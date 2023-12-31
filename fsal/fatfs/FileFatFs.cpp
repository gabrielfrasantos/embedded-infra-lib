#include "fsal/fatfs/FileFatFs.hpp"
#include "infra/util/EnumCast.hpp"
#include "infra/util/BoundedString.hpp"
#include "infra/util/ReallyAssert.hpp"

namespace fsal
{
    FileFatFs::FileFatFs(infra::BoundedConstString name)
        : name(name)
    {}

    void FileFatFs::Open(Mode mode)
    {
        really_assert(f_open(&file, name.begin(), infra::enum_cast(mode)) == FR_OK);
    }

    void FileFatFs::Close()
    {
        really_assert(f_close(&file) == FR_OK);
    }

    void FileFatFs::Read(infra::ByteRange buffer)
    {
        UINT br;
        really_assert(f_read(&file, buffer.begin(), buffer.size(), &br) == FR_OK);
    }

    void FileFatFs::Write(infra::ConstByteRange buffer)
    {
        UINT bw;
        really_assert(f_write(&file, buffer.begin(), buffer.size(), &bw) == FR_OK);
    }

    void FileFatFs::Seek(uint32_t offset)
    {
        really_assert(f_lseek(&file, offset) == FR_OK);
    }

    void FileFatFs::Truncate()
    {
        really_assert(f_truncate(&file) == FR_OK);
    }

    void FileFatFs::Flush()
    {
        really_assert(f_sync(&file) == FR_OK);
    }

    std::size_t FileFatFs::Size()
    {
        return f_size(&file);
    }
}