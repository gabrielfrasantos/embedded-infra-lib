#ifndef FSAL_INTERFACES_OBJECT_HPP
#define FSAL_INTERFACES_OBJECT_HPP

#include "infra/util/BoundedString.hpp"
#include "infra/util/EnumCast.hpp"
#include "infra/util/Function.hpp"

namespace fsal
{
    class Object
    {
    public:
        enum class Attributes : uint8_t
        {
            readOnly = 0x01u,
            hidden = 0x02u,
            system = 0x04u,
            directory = 0x10u,
            archive = 0x20u
        };

        virtual ~Object() = default;

        virtual void Exists(const infra::Function<void(bool)>& onDone) = 0;
        virtual void Create(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void Remove(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void Rename(infra::BoundedConstString oldName, infra::BoundedConstString newName, const infra::Function<void()>& onDone) = 0;
        virtual void ChangeAttributes(infra::BoundedConstString name, Attributes attributes, const infra::Function<void()>& onDone) = 0;
        virtual void ChangeDirectory(infra::BoundedConstString newDirectory, const infra::Function<void()>& onDone) = 0;
        virtual void GetWorkingDirectory(const infra::Function<void(const infra::BoundedConstString&)>& onDone) = 0;
    };


    inline Object::Attributes operator|(Object::Attributes lhs, Object::Attributes rhs)
    {
        return static_cast<Object::Attributes>(infra::enum_cast(lhs) | infra::enum_cast(rhs));
    }
}

#endif
