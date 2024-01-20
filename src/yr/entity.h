#pragma once

#include <type_traits>

class AbstractClass;
class ObjectClass;
class AbstractTypeClass;

struct YrEntity
{
    union
    {
        void*              object;
        AbstractClass*     yrObject;
        ObjectClass*       yrGameObject;
        AbstractTypeClass* yrTypeObject;
    };
    YrEntity() : object(nullptr) {}
    YrEntity(const YrEntity& other) : object(other.object) {}
    YrEntity(AbstractClass* yrObject) : yrObject(yrObject) {}
    YrEntity(ObjectClass* yrGameObject) : yrGameObject(yrGameObject) {}
    YrEntity(AbstractTypeClass* yrTypeObject) : yrTypeObject(yrTypeObject) {}

    inline YrEntity& operator=(AbstractClass* rhs)
    {
        yrObject = rhs;
        return *this;
    }
    inline YrEntity& operator=(ObjectClass* rhs)
    {
        yrGameObject = rhs;
        return *this;
    }
    inline YrEntity& operator=(AbstractTypeClass* rhs)
    {
        yrTypeObject = rhs;
        return *this;
    }

    inline operator AbstractClass*()
    {
        return yrObject;
    }
    inline operator ObjectClass*()
    {
        return yrGameObject;
    }
    inline operator AbstractTypeClass*()
    {
        return yrTypeObject;
    }

    inline bool operator==(const YrEntity& rhs) const
    {
        return object == rhs.object;
    }

    inline size_t GetHashValue() const
    {
        return reinterpret_cast<size_t>(object);
    }
};


template<>
struct std::hash<YrEntity>
{
    size_t operator()(const YrEntity& entity) const noexcept
    {
        return entity.GetHashValue();
    }
};
