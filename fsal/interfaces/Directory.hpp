#ifndef FSAL_INTERFACES_DIRECTORY_HPP
#define FSAL_INTERFACES_DIRECTORY_HPP

#include "fsal/interfaces/Object.hpp"

namespace fsal
{
    class Directory
        : public Object
    {
    public:
        struct Info
        {
            std::size_t size;
            Object::Attributes attributes;
            infra::BoundedConstString::WithStorage<64> name;
        };

        explicit Directory(infra::BoundedConstString name);
        ~Directory() override = default;

        virtual void Infomation(const infra::Function<void(const Info&)>& onDone) = 0;
    };
}

#endif
