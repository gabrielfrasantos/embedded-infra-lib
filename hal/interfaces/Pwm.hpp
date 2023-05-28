#ifndef HAL_PWM_HPP
#define HAL_PWM_HPP

#include "infra/util/Unit.hpp"

namespace hal
{
    class PwmChannel
    {
    public:
        virtual ~PwmChannel() = default;
    
        virtual void SetDutyCycle(infra::Percent value) = 0;
        virtual void SetDeadTime(uint8_t value) = 0;
    };

    class Pwm
        : public PwmChannel
    {
    public:
        virtual void SetFrequency(infra::Hertz value) = 0;
    };
}

#endif
