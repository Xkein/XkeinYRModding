#pragma once

template<class Lambda, int=(Lambda{}(), 0)>
constexpr bool is_constexpr_friendly(Lambda) { return true; }
constexpr bool is_constexpr_friendly(...) { return false; }

template<auto Data>
constexpr bool is_constexpr_var = is_constexpr_friendly([](){*Data;});
