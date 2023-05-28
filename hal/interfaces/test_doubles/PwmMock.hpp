#ifndef HAL_PWM_MOCK_HPP
#define HAL_PWM_MOCK_HPP

#include "hal/interfaces/Pwm.hpp"
#include "gmock/gmock.h"

namespace hal
{
    class PwmChannelMock
        : public hal::PwmChannel
    {
    public:
        MOCK_METHOD1(SetDutyCycle, void(infra::Percent value));
        MOCK_METHOD1(SetDeadTime, void(uint8_t value));
    };

    class PwmMock
        : public hal::Pwm
    {
    public:
        MOCK_METHOD1(SetFrequency, void(infra::Hertz value));
    };
}

#endif
