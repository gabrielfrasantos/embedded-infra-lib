#ifndef FSAL_INTERFACES_VOLUME_HPP
#define FSAL_INTERFACES_VOLUME_HPP

#include "infra/util/BoundedString.hpp"
#include "infra/util/Function.hpp"

namespace fsal
{
    class Volume
    {
    public:
        virtual ~Volume() = default;

        virtual void Mount() = 0;
        virtual void Unmount() = 0;
        virtual std::size_t FreeSpace() = 0;

        virtual void CreateDirectory(infra::BoundedConstString name) = 0;
        virtual void ChangeDirectory(infra::BoundedConstString name) = 0;
        virtual infra::BoundedConstString& GetWorkingDirectory() = 0;
    };
}

#endif
