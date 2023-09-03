#ifndef HAL_QUADRATURE_ENCODER_HPP
#define HAL_QUADRATURE_ENCODER_HPP

#include "infra/util/Function.hpp"
#include "infra/util/Unit.hpp"

namespace hal
{
    class QuadratureEncoder
    {
    public:
        enum class MotionDirection : uint8_t
        {
            forward,
            reverse,
        };

        virtual ~QuadratureEncoder() = default;

        virtual void Position(uint32_t position) = 0;
        virtual void Resolution(uint32_t resolution) = 0;

        virtual uint32_t Position() = 0;
        virtual uint32_t Resolution() = 0;

        virtual MotionDirection Direction() = 0;
        virtual void Direction(const infra::Function<void(MotionDirection)>& onDirectionChange) = 0;

        virtual uint32_t Speed() = 0;
    };
}

#endif
