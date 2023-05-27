#ifndef HAL_PWM_INPUT_HPP
#define HAL_PWM_INPUT_HPP

#include "infra/util/AutoResetFunction.hpp"
#include "infra/util/Unit.hpp"

namespace hal
{
    template<class Unit, class Storage>
    class PwmInput
    {
    protected:
        PwmInput() = default;
        PwmInput(const PwmInput&) = delete;
        PwmInput& operator=(const PwmInput&) = delete;
        ~PwmInput() = default;

    public:
        virtual void Measure(const infra::Function<void(infra::Quantity<Unit, Storage> value)>& onDone) = 0;
    };

    class PwmInputImplBase
    {
    protected:
        ~PwmInputImplBase() = default;

    public:
        virtual void Measure(const infra::Function<void(int32_t value)>& onDone) = 0;
    };

    template<class Conversion, class Unit, class Storage, class Impl>
    class PwmInputConverter
        : public PwmInput<Unit, Storage>
        , public Impl
    {
    public:
        template<class... Args>
        PwmInputConverter(Args&&... args);

        void Measure(const infra::Function<void(infra::Quantity<Unit, Storage> value)>& onDone);

    private:
        infra::AutoResetFunction<void(infra::Quantity<Unit, Storage> value)> onDone;
    };

    ////    Implementation    ////

    template<class Conversion, class Unit, class Storage, class Impl>
    template<class... Args>
    PwmInputConverter<Conversion, Unit, Storage, Impl>::PwmInputConverter(Args&&... args)
        : Impl(std::forward<Args>(args)...)
    {}

    template<class Conversion, class Unit, class Storage, class Impl>
    void PwmInputConverter<Conversion, Unit, Storage, Impl>::Measure(const infra::Function<void(infra::Quantity<Unit, Storage> value)>& onDone)
    {
        this->onDone = onDone;
        Impl::Measure([this](int32_t value)
            { this->onDone(infra::Quantity<Conversion, Storage>(value)); });
    }
}

#endif
