#ifndef HAL_PWM_INPUT_MOCK_HPP
#define HAL_PWM_INPUT_MOCK_HPP

#include "hal/interfaces/PwmInput.hpp"
#include "infra/util/Unit.hpp"
#include "gmock/gmock.h"

namespace hal
{
    class PinInputImplMock
        : public PwmInputImplBase
    {
    public:
        MOCK_METHOD1(Measure, void(const infra::Function<void(int32_t value)>& onDone));
    };
}

#endif
