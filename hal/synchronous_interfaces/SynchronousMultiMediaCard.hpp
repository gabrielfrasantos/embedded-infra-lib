#ifndef SYNCHRONOUS_HAL_MULTI_MEDIA_CARD_HPP
#define SYNCHRONOUS_HAL_MULTI_MEDIA_CARD_HPP

#include "infra/util/ByteRange.hpp"

namespace hal
{
    class SynchronousMultiMediaCard
    {
    public:
        virtual ~SynchronousMultiMediaCard() = default;

        virtual bool IsLocked() = 0;
        virtual std::size_t CardSize() = 0;
        virtual std::size_t SectorSize() = 0;
        virtual std::size_t BlockSize() = 0;
        virtual void Write(infra::ConstByteRange data, std::size_t sector) = 0;
        virtual void Read(infra::ByteRange data, std::size_t sector) = 0;
    };
}

#endif
