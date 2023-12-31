#ifndef FSAL_INTERFACES_FILE_HPP
#define FSAL_INTERFACES_FILE_HPP

#include "fsal/interfaces/Object.hpp"
#include "infra/util/ByteRange.hpp"

namespace fsal
{
    class File
        : public Item
    {
    public:
        enum class Mode : uint8_t
        {
            read = 0x01u,
            write = 0x02u,
            openExisting = 0x00u,
            createNew = 0x04u,
            createAlways = 0x08u,
            openAlways = 0x10u,
            openAppend = 0x30u,
        };

        ~File() override = default;

        virtual void Open(Mode mode) = 0;
        virtual void Close() = 0;
        virtual void Read(infra::ByteRange buffer) = 0;
        virtual void Write(infra::ConstByteRange buffer) = 0;
        virtual void Seek(uint32_t offset) = 0;
        virtual void Truncate() = 0;
        virtual void Flush() = 0;
        virtual std::size_t Size() = 0;
    };

    inline File::Mode operator|(File::Mode lhs, File::Mode rhs)
    {
        return static_cast<File::Mode>(infra::enum_cast(lhs) | infra::enum_cast(rhs));
    }
}

#endif
