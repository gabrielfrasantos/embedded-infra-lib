#ifndef FSAL_INTERFACES_OBJECT_HPP
#define FSAL_INTERFACES_OBJECT_HPP

#include "infra/util/BoundedString.hpp"
#include "infra/util/EnumCast.hpp"

namespace fsal
{
    class Item
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

        virtual ~Item() = default;
        virtual infra::BoundedConstString& Name() = 0;
    };

    class Manager
    {
    public:
        virtual ~Manager() = default;

        virtual bool DoesExist(Item& item) = 0;
        virtual bool IsFile(Item& item) = 0;
        virtual bool IsDirectory(Item& item) = 0;
        virtual void Remove(Item& item) = 0;
        virtual void Rename(Item& item, infra::BoundedConstString newName) = 0;
        virtual void ChangeAttributes(Item& item, Item::Attributes attributes) = 0;
    };

    inline Item::Attributes operator|(Item::Attributes lhs, Item::Attributes rhs)
    {
        return static_cast<Item::Attributes>(infra::enum_cast(lhs) | infra::enum_cast(rhs));
    }
}

#endif
