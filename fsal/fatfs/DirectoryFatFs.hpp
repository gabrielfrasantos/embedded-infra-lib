#ifndef FSAL_FATFS_DIRECTORY_FATFS_HPP
#define FSAL_FATFS_DIRECTORY_FATFS_HPP

#include "fsal/interfaces/Directory.hpp"
#include "infra/util/BoundedString.hpp"
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
        Directory::Info& Infomation() override;
        infra::BoundedConstString& Name() override;

    private:
        infra::BoundedConstString::WithStorage<32> name;
        Directory::Info information;
        DIR directory;
    };
}

#endif
