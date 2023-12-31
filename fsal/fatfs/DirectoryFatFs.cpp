#include "fsal/fatfs/DirectoryFatFs.hpp"

namespace fsal
{
    DirectoryFatFs::DirectoryFatFs(infra::BoundedConstString name)
        : name(name)
    {}

    Directory::Info& DirectoryFatFs::Infomation()
    {
        return information;
    }
}