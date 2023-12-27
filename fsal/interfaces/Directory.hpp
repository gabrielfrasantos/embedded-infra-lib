#ifndef FSAL_INTERFACES_DIRECTORY_HPP
#define FSAL_INTERFACES_DIRECTORY_HPP

#include "infra/util/BoundedString.hpp"
#include "infra/util/EnumCast.hpp"
#include "infra/util/Function.hpp"

namespace fsal
{
    class DirectoryManager
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

        virtual ~DirectoryManager() = default;

        virtual void Create(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void Remove(infra::BoundedConstString name, const infra::Function<void()>& onDone) = 0;
        virtual void Rename(infra::BoundedConstString oldName, infra::BoundedConstString newName, const infra::Function<void()>& onDone) = 0;
        virtual void ChangeAttributes(infra::BoundedConstString name, Attributes attributes, const infra::Function<void()>& onDone) = 0;
        virtual void ChangeDirectory(infra::BoundedConstString newDirectory, const infra::Function<void()>& onDone) = 0;
        virtual void GetWorkingDirectory(const infra::Function<void(const infra::BoundedConstString&)>& onDone) = 0;
    };

    class Directory
    {
        struct Info
        {
            std::size_t size;
            DirectoryManager::Attributes attributes;
            infra::BoundedConstString::WithStorage<64> name;
        };

        explicit Directory(infra::BoundedConstString name);
        virtual ~Directory() = default;

        void Infomation(const infra::Function<void(const Info&)>& onDone);
    };

    inline DirectoryManager::Attributes operator|(DirectoryManager::Attributes lhs, DirectoryManager::Attributes rhs)
    {
        return static_cast<DirectoryManager::Attributes>(infra::enum_cast(lhs) | infra::enum_cast(rhs));
    }
}

#endif
