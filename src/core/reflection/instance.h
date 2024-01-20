#pragma once

#include "core/string/ustring.h"
#include <rttr/registration_friend.h>
#include <rttr/type>

template<typename T>
class Instance
{
    friend class Serializer;
    friend class ReflectionInstance;

public:
    Instance() : m_type(Type::InvalidType), m_instance(nullptr) {}
    Instance(const rttr::type& type, T* ptr) : m_type(type), m_instance(ptr) {}
    Instance(const Instance& other) : m_type(other.m_type), m_instance(other.m_instance) {}

    template<typename U /*, typename = typename std::enable_if<std::is_safely_castable<T*, U*>::value>::type */>
    Instance<T>& operator=(const Instance<U>& other)
    {
        m_type     = other.m_type;
        m_instance = static_cast<T*>(other.m_instance);
        return *this;
    }

    Instance<T>& operator=(const Instance<T>& other)
    {
        m_type     = other.m_type;
        m_instance = other.m_instance;
        return *this;
    }

    const rttr::type& GetType() const
    {
        return m_type;
    }

    void SetType(const rttr::type& type)
    {
        m_type = type;
    }

    StringView GetTypeName() const
    {
        auto view = m_type.get_name();
        return StringView(view.begin(), view.end());
    }

    T* GetPtr()
    {
        return m_instance;
    }

    const T* GetPtr() const
    {
        return m_instance;
    }

    void SetInstancePtr(T* ptr)
    {
        m_instance = ptr;
    }

    bool operator==(const T* ptr) const
    {
        return (m_instance == ptr);
    }

    bool operator!=(const T* ptr) const
    {
        return (m_instance != ptr);
    }

    bool operator==(const Instance<T>& rhs_ptr) const
    {
        return (m_instance == rhs_ptr.m_instance);
    }

    bool operator!=(const Instance<T>& rhs_ptr) const
    {
        return (m_instance != rhs_ptr.m_instance);
    }

    template<typename T1>
    operator T1*()
    {
        return static_cast<T1*>(m_instance);
    }

    template<typename T1>
    operator const T1*() const
    {
        return static_cast<T1*>(m_instance);
    }

    template<typename T1>
    operator Instance<T1>()
    {
        return Instance<T1>(m_type, (T1*)m_instance);
    }

    template<typename T1>
    operator const Instance<T1>() const
    {
        return Instance<T1>(m_type, (T1*)m_instance);
    }

    T* operator->()
    {
        return m_instance;
    }
    const T* operator->() const
    {
        return m_instance;
    }

    T& operator*()
    {
        return *m_instance;
    }
    const T& operator*() const
    {
        return *static_cast<const T*>(m_instance);
    }

    operator bool() const
    {
        return m_instance != nullptr;
    }

private:
    rttr::type m_type;
    T*         m_instance;
};

#define REFLECTION_NEW(type, ...) Instance<type>(::rttr::type::get<type>(), new type(__VA_ARGS__))
#define REFLECTION_DELETE(instance) \
    if (instance) \
    { \
        delete instance.operator->(); \
        instance.SetInstancePtr(nullptr); \
    }

class ReflectionInstance : public Instance<void*>
{
public:
    ReflectionInstance() : Instance() {}
    ReflectionInstance(const rttr::type& type, void* ptr) : Instance(type, (void**)ptr) {}
    ReflectionInstance(const Instance& other) : Instance(other) {}
    template<typename T>
    ReflectionInstance(const Instance<T>& other) : Instance(other.m_type, (void**)other.m_instance)
    {}

    void* GetPtr()
    {
        return m_instance;
    }

    const void* GetPtr() const
    {
        return m_instance;
    }

    void SetInstancePtr(void* ptr)
    {
        m_instance = (void**)ptr;
    }
};
