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

        virtual void Mount(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void Unmount(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void CreateVolume(infra::BoundedConstString oldName, infra::BoundedConstString newName, const infra::Function<void()>& onDone) = 0;
        virtual void CreatePartition(const infra::Function<void()>& onDone) = 0;
        virtual void SetLabel(infra::BoundedConstString newDirectory, const infra::Function<void()>& onDone) = 0;
        virtual void GetLabel(const infra::Function<void(const infra::BoundedConstString&)>& onDone) = 0;
        virtual void GetFreeSpace(const infra::Function<void(const infra::BoundedConstString&)>& onDone) = 0;
    };
}

#endif
