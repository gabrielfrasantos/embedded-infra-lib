#include "fsal/fatfs/DirectoryFatFs.hpp"
#include "fsal/interfaces/Directory.hpp"
#include "infra/util/EnumCast.hpp"

namespace fsal
{
    DirectoryFatFs::DirectoryFatFs(infra::BoundedConstString name)
        : Directory(name)
        , dirName(name)
    {}

    void DirectoryFatFs::Infomation(const infra::Function<void(const Directory::Info&)>& onDone)
    {

    }

    void DirectoryFatFs::Exists(const infra::Function<void(bool)>& onDone)
    {
        FILINFO info;

        onDone(f_stat(dirName.cbegin(), &info) == FR_OK);
    }

    void DirectoryFatFs::Create(infra::BoundedConstString name, const infra::Function<void()>& onDone)
    {
        Check(f_mkdir(name.cbegin()), onDone);
    }

    void DirectoryFatFs::Remove(infra::BoundedConstString name, const infra::Function<void()>& onDone)
    {
        Check(f_unlink(name.cbegin()), onDone);
    }

    void DirectoryFatFs::Rename(infra::BoundedConstString oldName, infra::BoundedConstString newName, const infra::Function<void()>& onDone)
    {
        Check(f_rename(oldName.cbegin(), newName.cbegin()), onDone);
    }

    void DirectoryFatFs::ChangeAttributes(infra::BoundedConstString name, Attributes attributes, const infra::Function<void()>& onDone)
    {
        Check(f_chmod(name.cbegin(), infra::enum_cast(attributes), 0xff), onDone);
    }

    void DirectoryFatFs::ChangeDirectory(infra::BoundedConstString newDirectory, const infra::Function<void()>& onDone)
    {
        Check(f_chdir(newDirectory.cbegin()), onDone);
    }

    void DirectoryFatFs::GetWorkingDirectory(const infra::Function<void(const infra::BoundedConstString&)>& onDone)
    {
        infra::BoundedString::WithStorage<32> currentDirectory;
        Check(f_getcwd(currentDirectory.begin(), currentDirectory.max_size()), onDone, currentDirectory);
    }

    void DirectoryFatFs::Check(FRESULT result, const infra::Function<void()>& onDone) const
    {
        if (result == FR_OK)
            onDone();
        else
            std::abort();
    }

    void DirectoryFatFs::Check(FRESULT result, const infra::Function<void(const infra::BoundedConstString&)>& onDone, const infra::BoundedString& data) const
    {
        if (result == FR_OK)
            onDone(data);
        else
            std::abort();
    }
}