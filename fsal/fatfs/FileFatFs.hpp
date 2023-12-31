#ifndef FSAL_FATFS_FILE_FATFS_HPP
#define FSAL_FATFS_FILE_FATFS_HPP

#include "fsal/interfaces/File.hpp"
#include "infra/util/BoundedString.hpp"
#include "source/ff.h"

namespace fsal
{
    class FileFatFs
        : public File
    {
    public:
        explicit FileFatFs(infra::BoundedConstString name);
        ~FileFatFs() override = default;

        // Implementation of File
        void Open(Mode mode) override;
        void Close() override;
        void Read(infra::ByteRange buffer) override;
        void Write(infra::ConstByteRange buffer) override;
        void Seek(uint32_t offset) override;
        void Truncate() override;
        void Flush() override;
        std::size_t Size() override;

    private:
        infra::BoundedConstString::WithStorage<32> name;
        FIL file;
    };
}

#endif
