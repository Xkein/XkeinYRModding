#pragma once
#include <memory>
#include <vector>

template<class Lambda, int=(Lambda{}(), 0)>
constexpr bool is_constexpr_friendly(Lambda) { return true; }
constexpr bool is_constexpr_friendly(...) { return false; }

template<auto Data>
constexpr bool is_constexpr_var = is_constexpr_friendly([](){*Data;});

// Core concept to detect std::shared_ptr
template <typename T>
concept is_shared_ptr = requires {
    // 1. Ensure the type contains 'element_type' (filters out basic non-container types)
    typename std::remove_cvref_t<T>::element_type;
} && std::same_as<
    // 2. Strip qualifiers (const, volatile, reference) and check if it exactly matches std::shared_ptr
    std::remove_cvref_t<T>, 
    std::shared_ptr<typename std::remove_cvref_t<T>::element_type>
>;

// Convenience variable template (constexpr bool) matching the concept
template <typename T>
inline constexpr bool is_shared_ptr_v = is_shared_ptr<T>;

// Checks if executing 'delete p' on a pointer T* is valid
template <typename T>
concept is_deletable = requires(T* p) {
    delete p;
};

template <typename T>
inline constexpr bool is_deletable_v = is_deletable<T>;

// Detect std::vector<T>
template <typename T>
struct is_std_vector : std::false_type {};
template <typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc>> : std::true_type {};
template <typename T>
inline constexpr bool is_std_vector_v = is_std_vector<std::remove_cv_t<std::remove_reference_t<T>>>::value;
