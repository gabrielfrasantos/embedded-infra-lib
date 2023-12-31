#ifndef FSAL_INTERFACES_DIRECTORY_HPP
#define FSAL_INTERFACES_DIRECTORY_HPP

#include "fsal/interfaces/Object.hpp"

namespace fsal
{
    class Directory
        : public Item
    {
    public:
        struct Info
        {
            std::size_t size;
            Item::Attributes attributes;
            infra::BoundedConstString::WithStorage<64> name;
        };

        ~Directory() override = default;

        virtual Info& Infomation() = 0;
    };
}

#endif
