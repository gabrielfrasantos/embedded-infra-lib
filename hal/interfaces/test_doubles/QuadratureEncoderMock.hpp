#ifndef HAL_PWM_INPUT_MOCK_HPP
#define HAL_PWM_INPUT_MOCK_HPP

#include "hal/interfaces/QuadratureEncoder.hpp"
#include "infra/util/Unit.hpp"
#include "gmock/gmock.h"

namespace hal
{
    class QuadratureEncoderMock
        : public QuadratureEncoder
    {
    public:
        MOCK_METHOD1(SetMaxixumPosition, void(uint32_t));
        MOCK_METHOD1(SetCurrentPosition, void(uint32_t));
        MOCK_METHOD0(GetPosition, uint32_t());
        MOCK_METHOD0(GetDirection, Direction());
        MOCK_METHOD0(GetSpeed, infra::PulsesPerSecond());
    };
}

#endif
