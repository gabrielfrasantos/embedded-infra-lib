#ifndef HAL_PWM_HPP
#define HAL_PWM_HPP

#include "infra/util/Unit.hpp"

namespace hal
{
    using Hertz = infra::Quantity<infra::Hertz, uint32_t>;
    using Percent = infra::Quantity<infra::Percent, uint8_t>;

    class PwmChannel
    {
    public:
        virtual ~PwmChannel() = default;

        virtual void Start(Percent dutyCycle) = 0;
        virtual void Stop() = 0;
        virtual void High() = 0;
        virtual void Low() = 0;
    };

    class Pwm
    {
    public:
        virtual void SetBaseFrequency(Hertz baseFrequency) = 0;
        virtual void Start(Percent globalDutyCycle) = 0;
        virtual void Stop() = 0;
    };
}

#endif
