#ifndef HAL_QUADRATURE_ENCODER_HPP
#define HAL_QUADRATURE_ENCODER_HPP

#include "infra/util/Unit.hpp"

namespace hal
{
    class QuadratureEncoder
    {
    public:
        enum class Direction : uint8_t
        {
            forward,
            reverse,
        };

        virtual ~QuadratureEncoder() = default;

        virtual void SetMaxixumPosition(uint32_t) = 0;
        virtual void SetCurrentPosition(uint32_t) = 0;
        virtual uint32_t GetPosition() = 0;
        virtual Direction GetDirection() = 0;
        virtual infra::PulsesPerSecond GetSpeed() = 0;
    };
}

#endif
