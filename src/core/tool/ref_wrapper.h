#pragma once
#include <type_traits>

// used by javascript wrapper
template <class _Ty>
class ref_wrapper
{
public:
    static_assert(std::is_object_v<_Ty> || std::is_function_v<_Ty>,
        "ref_wrapper<T> requires T to be an object type or a function type.");

    using type = _Ty;
    ref_wrapper() : _Ptr(nullptr) {}

    ref_wrapper(_Ty&& _Val) {
        _Ptr = std::addressof(_Val);
    }
    ref_wrapper(_Ty& _Val) {
        _Ptr = std::addressof(_Val);
    }

    void set(_Ty* ptr) {
        _Ptr = ptr;
    }

    ref_wrapper& operator=(const ref_wrapper& other) {
        // set value
        *_Ptr = *other._Ptr;
        return *this;
    }


    operator _Ty&() const noexcept {
        return *_Ptr;
    }

    _Ty& get() const noexcept {
        return *_Ptr;
    }

private:
    _Ty* _Ptr{};
};
