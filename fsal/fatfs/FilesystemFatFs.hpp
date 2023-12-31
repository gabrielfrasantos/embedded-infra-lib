#ifndef FSAL_FATFS_FILESYSTEM_FATFS_HPP
#define FSAL_FATFS_FILESYSTEM_FATFS_HPP

#include "fsal/fatfs/DirectoryFatFs.hpp"
#include "fsal/fatfs/FileFatFs.hpp"
#include "fsal/interfaces/Directory.hpp"
#include "fsal/interfaces/File.hpp"
#include "fsal/interfaces/Volume.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/BoundedVector.hpp"
#include "hal/synchronous_interfaces/SynchronousDisk.hpp"
#include "source/ff.h"
#include "infra/util/SharedPtr.hpp"

#if FF_STR_VOLUME_ID != 0
#error "FF_STR_VOLUME_ID has to be equal 0!"
#endif

namespace fsal
{
    class FileSystemFatFs
        : public fsal::Volume
        , public fsal::Manager
    {
    public:
        /*
        WithMaxDirectoriesAndFiles<10, 20>
        */

        explicit FileSystemFatFs(infra::BoundedVector<FileFatFs>& files, infra::BoundedVector<DirectoryFatFs>& directories, hal::SynchronousDisk& interface);
        ~FileSystemFatFs() override;

        // Implementation of Volume
        void Mount() override;
        void Unmount() override;
        std::size_t FreeSpace() override;
        void CreateDirectory(infra::BoundedConstString name) override;
        void ChangeDirectory(infra::BoundedConstString name) override;
        infra::BoundedConstString& GetWorkingDirectory() override;

        // Implementation of Manager
        bool DoesExist(Item& item) override;
        bool IsFile(Item& item) override;
        bool IsDirectory(Item& item) override;
        void Remove(Item& item) override;
        void Rename(Item& item, infra::BoundedConstString newName) override;
        void ChangeAttributes(Item& item, Item::Attributes attributes) override;

        infra::SharedPtr<fsal::Directory> Directory(infra::BoundedConstString path);
        infra::SharedPtr<fsal::File> File(infra::BoundedConstString path);

    private:
        class FormatPath
        {
        public:
            explicit FormatPath(infra::BoundedConstString& path, infra::BoundedConstString& item);
            ~FormatPath();

            infra::BoundedConstString& Path();

        private:
            infra::BoundedConstString& path;
            infra::BoundedConstString& item;
        };

    private:
        infra::BoundedVector<FileFatFs>& files;
        infra::BoundedVector<DirectoryFatFs>& directories;
        hal::SynchronousDisk& interface;
        FATFS filesystem{};
        infra::BoundedConstString::WithStorage<12> label;
        infra::BoundedConstString::WithStorage<FF_SFN_BUF + 1> path;
        infra::BoundedConstString::WithStorage<FF_SFN_BUF + 1> workindDirectory;
    };
}

#endif
