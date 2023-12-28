#ifndef FSAL_FATFS_DIRECTORY_FATFS_HPP
#define FSAL_FATFS_DIRECTORY_FATFS_HPP

#include "fsal/interfaces/Directory.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/Function.hpp"
#include "source/ff.h"

namespace fsal
{
    class DirectoryFatFs
        : public Directory
    {
    public:
        explicit DirectoryFatFs(infra::BoundedConstString name);
        ~DirectoryFatFs() override;

        // Implementation of Directory
        void Infomation(const infra::Function<void(const Directory::Info&)>& onDone) override;

        // Implementation of Object
        void Exists(const infra::Function<void(bool)>& onDone) override;
        void Create(infra::BoundedConstString name, const infra::Function<void()>& onDone) override;
        void Remove(infra::BoundedConstString name, const infra::Function<void()>& onDone) override;
        void Rename(infra::BoundedConstString oldName, infra::BoundedConstString newName, const infra::Function<void()>& onDone) override;
        void ChangeAttributes(infra::BoundedConstString name, Attributes attributes, const infra::Function<void()>& onDone) override;
        void ChangeDirectory(infra::BoundedConstString newDirectory, const infra::Function<void()>& onDone) override;
        void GetWorkingDirectory(const infra::Function<void(const infra::BoundedConstString&)>& onDone) override;

    private:
        void Check(FRESULT result, const infra::Function<void()>& onDone) const;
        void Check(FRESULT result, const infra::Function<void(const infra::BoundedConstString&)>& onDone, const infra::BoundedString& data) const;

    private:
        infra::BoundedConstString::WithStorage<32> dirName;
        DIR dirType;
    };
}

#endif
