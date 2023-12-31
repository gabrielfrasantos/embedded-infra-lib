#include "fsal/fatfs/FilesystemFatFs.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/SharedPtr.hpp"
#include "source/ff.h"
#include "fsal/fatfs/DriverFatFs.hpp"

namespace fsal
{
    FileSystemFatFs::FormatPath::FormatPath(infra::BoundedConstString& path, infra::BoundedConstString& item)
        : path(path)
        , item(item)
    {
        path.pop_back();
        path += item;
    }

    FileSystemFatFs::FormatPath::~FormatPath()
    {
        path.erase(path.find(item), item.size());
        path += '\0';
    }

    infra::BoundedConstString& FileSystemFatFs::FormatPath::Path()
    {
        return path;
    }

    FileSystemFatFs::FileSystemFatFs(infra::BoundedVector<FileFatFs>& files, infra::BoundedVector<DirectoryFatFs>& directories, hal::SynchronousDisk& interface)
        : files(files)
        , directories(directories)
        , interface(interface)
    {
        DriverFatFs::Instance().RegisterDriver(interface);
    }

    FileSystemFatFs::~FileSystemFatFs()
    {
        DriverFatFs::Instance().UnregisterDriver(interface);
    }

    void FileSystemFatFs::Mount()
    {
        really_assert(f_mount(&filesystem, path.cbegin(), 0) == FR_OK);
    }

    void FileSystemFatFs::Unmount()
    {
        really_assert(f_unmount(path.cbegin()) == FR_OK);
    }

    std::size_t FileSystemFatFs::FreeSpace()
    {
        DWORD freeClusters;
        FATFS* fs;

        really_assert(f_getfree(path.cbegin(), &freeClusters, &fs) == FR_OK);

        return freeClusters * fs->csize;
    }

    void FileSystemFatFs::CreateDirectory(infra::BoundedConstString name)
    {
        really_assert(f_mkdir(FileSystemFatFs::FormatPath(path, name).Path().cbegin()) == FR_OK);
    }

    void FileSystemFatFs::ChangeDirectory(infra::BoundedConstString name)
    {
        really_assert(f_chdir(FileSystemFatFs::FormatPath(path, name).Path().cbegin()) == FR_OK);
    }

    infra::BoundedConstString& FileSystemFatFs::GetWorkingDirectory()
    {
        really_assert(f_getcwd(const_cast<TCHAR *>(workindDirectory.begin()), workindDirectory.max_size()) == FR_OK);
        return workindDirectory;
    }

    bool FileSystemFatFs::DoesExist(Item& item)
    {
        FILINFO info;
        return f_stat(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin(), &info) == FR_OK;
    }

    bool FileSystemFatFs::IsFile(Item& item)
    {
        FILINFO info;
        auto status = f_stat(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin(), &info) == FR_OK;

        return status && !(info.fattrib & AM_DIR);
    }

    bool FileSystemFatFs::IsDirectory(Item& item)
    {
        FILINFO info;
        auto status = f_stat(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin(), &info) == FR_OK;

        return status && info.fattrib & AM_DIR;
    }

    void FileSystemFatFs::Remove(Item& item)
    {
        really_assert(f_unlink(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin()) == FR_OK);
    }

    void FileSystemFatFs::Rename(Item& item, infra::BoundedConstString newName)
    {
        really_assert(f_rename(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin(), FileSystemFatFs::FormatPath(path, newName).Path().cbegin()) == FR_OK);
    }

    void FileSystemFatFs::ChangeAttributes(Item& item, Item::Attributes attributes)
    {
        really_assert(f_chmod(FileSystemFatFs::FormatPath(path, item.Name()).Path().cbegin(), infra::enum_cast(attributes), 0xff) == FR_OK);
    }

    infra::SharedPtr<fsal::Directory> FileSystemFatFs::Directory(infra::BoundedConstString path)
    {
        really_assert(!directories.full());
        directories.emplace_back(path);
        return infra::UnOwnedSharedPtr(directories.back());
    }

    infra::SharedPtr<fsal::File> FileSystemFatFs::File(infra::BoundedConstString path)
    {
        really_assert(!files.full());
        files.emplace_back(path);
        return infra::UnOwnedSharedPtr(files.back());
    }
}