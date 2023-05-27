#ifndef HAL_PWM_HPP
#define HAL_PWM_HPP

#include "infra/util/Unit.hpp"

namespace hal
{
    class PwmChannel
    {
    protected:
        PwmChannel() = default;

        PwmChannel(const PwmChannel&) = delete;
        PwmChannel& operator=(const PwmChannel&) = delete;
        ~PwmChannel() = default;

    public:
        virtual void SetDutyCycle(infra::Percent value) = 0;
        virtual void SetDeadTime(uint8_t value) = 0;
    };

    class Pwm
        : public PwmChannel
    {
    protected:
        Pwm() = default;

        Pwm(const Pwm&) = delete;
        Pwm& operator=(const Pwm&) = delete;
        ~Pwm() = default;

    public:
        virtual void SetFrequency(infra::Hertz value) = 0;
    };
}

#endif
