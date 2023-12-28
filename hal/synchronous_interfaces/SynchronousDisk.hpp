#ifndef SYNCHRONOUS_HAL_DISK_HPP
#define SYNCHRONOUS_HAL_DISK_HPP

#include "infra/util/ByteRange.hpp"

namespace hal
{
    class SynchronousDisk
    {
    public:
        enum class Status : uint8_t
        {
            ok,
            notInitialized,
            noDiskAvailable,
            writeProtected,
        };

        virtual ~SynchronousDisk() = default;

        virtual void Initialize() = 0;
        virtual void Deinitialize() = 0;
        virtual Status Status() const = 0;
        virtual std::size_t SectorSize() = 0;
        virtual std::size_t MediaSize() = 0;
        virtual std::size_t BlockSize() = 0;
        virtual void Sync() = 0;
        virtual void Write(infra::ConstByteRange data, std::size_t sector) = 0;
        virtual void Read(infra::ByteRange data, std::size_t sector) = 0;
    };
}

#endif
