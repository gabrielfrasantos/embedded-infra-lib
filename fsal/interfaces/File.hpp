#ifndef FSAL_INTERFACES_FILE_HPP
#define FSAL_INTERFACES_FILE_HPP

#include "fsal/interfaces/Object.hpp"

namespace fsal
{
    class File
        : public Object
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

        explicit File(infra::BoundedConstString name, Mode mode);
        ~File() override = default;

        virtual void Open(const infra::Function<void()>& onDone) = 0;
        virtual void Close(const infra::Function<void()>& onDone) = 0;
        virtual void Read(const infra::Function<void()>& onDone) = 0;
        virtual void Write(const infra::Function<void()>& onDone) = 0;
        virtual void Seek(const infra::Function<void()>& onDone) = 0;
        virtual void Truncate(const infra::Function<void()>& onDone) = 0;
        virtual void Flush(const infra::Function<void()>& onDone) = 0;
        virtual void Size(const infra::Function<void(std::size_t)>& onDone) = 0;
    };

    inline File::Mode operator|(File::Mode lhs, File::Mode rhs)
    {
        return static_cast<File::Mode>(infra::enum_cast(lhs) | infra::enum_cast(rhs));
    }
}

#endif
