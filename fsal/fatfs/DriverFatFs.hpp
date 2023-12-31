#ifndef FSAL_FATFS_DRIVER_FATFS_HPP
#define FSAL_FATFS_DRIVER_FATFS_HPP

#include "infra/util/BoundedVector.hpp"
#include "hal/synchronous_interfaces/SynchronousDisk.hpp"
#include "infra/util/InterfaceConnector.hpp"
#include "source/ff.h"

#if FF_STR_VOLUME_ID != 0
#error "FF_STR_VOLUME_ID has to be equal 0!"
#endif

namespace fsal
{
    class DriverFatFs
        : public infra::InterfaceConnector<DriverFatFs>
    {
    public:
        void RegisterDriver(hal::SynchronousDisk& interface);
        void UnregisterDriver(hal::SynchronousDisk& interface);

        hal::SynchronousDisk& Interface(uint8_t index);

    private:
        struct Driver
        {
            hal::SynchronousDisk& interface;

            explicit Driver(hal::SynchronousDisk& interface)
                : interface(interface)
            {}
            ~Driver() = default;

            Driver& operator=(Driver&& other) noexcept
            {
                this->interface = other.interface;
                return *this;
            }
        };

        infra::BoundedVector<Driver>::WithMaxSize<FF_VOLUMES> drivers;
    };
}

#endif
