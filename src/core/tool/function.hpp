#pragma once

// https://stackoverflow.com/a/55701361
template<typename T, bool noexcept_state = true>
struct make_noexcept { using type = T; };

template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) noexcept, noexcept_state> { using type = R(Args...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const noexcept, noexcept_state> { using type = R(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile noexcept, noexcept_state> { using type = R(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile noexcept, noexcept_state> { using type = R(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) noexcept, noexcept_state> { using type = R(Args..., ...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const noexcept, noexcept_state> { using type = R(Args..., ...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile noexcept, noexcept_state> { using type = R(Args..., ...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile noexcept, noexcept_state> { using type = R(Args..., ...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) & noexcept, noexcept_state> { using type = R(Args...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const & noexcept, noexcept_state> { using type = R(Args...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile & noexcept, noexcept_state> { using type = R(Args...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile & noexcept, noexcept_state> { using type = R(Args...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) & noexcept, noexcept_state> { using type = R(Args..., ...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const & noexcept, noexcept_state> { using type = R(Args..., ...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile & noexcept, noexcept_state> { using type = R(Args..., ...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile & noexcept, noexcept_state> { using type = R(Args..., ...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) && noexcept, noexcept_state> { using type = R(Args...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const && noexcept, noexcept_state> { using type = R(Args...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile && noexcept, noexcept_state> { using type = R(Args...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile && noexcept, noexcept_state> { using type = R(Args...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) && noexcept, noexcept_state> { using type = R(Args..., ...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const && noexcept, noexcept_state> { using type = R(Args..., ...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile && noexcept, noexcept_state> { using type = R(Args..., ...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile && noexcept, noexcept_state> { using type = R(Args..., ...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) noexcept, noexcept_state> { using type = R(C::*)(Args...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const noexcept, noexcept_state> { using type = R(C::*)(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile noexcept, noexcept_state> { using type = R(C::*)(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile noexcept, noexcept_state> { using type = R(C::*)(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const noexcept, noexcept_state> { using type = R(C::*)(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile noexcept, noexcept_state> { using type = R(C::*)(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile noexcept, noexcept_state> { using type = R(C::*)(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) & noexcept, noexcept_state> { using type = R(C::*)(Args...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const & noexcept, noexcept_state> { using type = R(C::*)(Args...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile & noexcept, noexcept_state> { using type = R(C::*)(Args...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile & noexcept, noexcept_state> { using type = R(C::*)(Args...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) & noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const & noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile & noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile & noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) && noexcept, noexcept_state> { using type = R(C::*)(Args...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const && noexcept, noexcept_state> { using type = R(C::*)(Args...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile && noexcept, noexcept_state> { using type = R(C::*)(Args...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile && noexcept, noexcept_state> { using type = R(C::*)(Args...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) && noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const && noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile && noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile && noexcept, noexcept_state> { using type = R(C::*)(Args..., ...) const volatile && noexcept(noexcept_state); };

// MSVC++ 2019 (v142) doesn't allow `noexcept(x)` with a template parameter `x` in the template specialization list.
// (e.g., `struct make_noexcept<R(Args...) noexcept(noexcept_state)>` gives - C2057: expected constant expression)
// GCC 7.1.0 and Clang 5.0.0 (and later versions) were tested and do allow this, so MSVC++ is probably wrong.
// $ g++ prog.cc -Wall -Wextra -std=c++17 -pedantic
// $ clang++ prog.cc -Wall -Wextra -std=c++17 -pedantic

template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...), noexcept_state> { using type = R(Args...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const, noexcept_state> { using type = R(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile, noexcept_state> { using type = R(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile, noexcept_state> { using type = R(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...), noexcept_state> { using type = R(Args..., ...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const, noexcept_state> { using type = R(Args..., ...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile, noexcept_state> { using type = R(Args..., ...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile, noexcept_state> { using type = R(Args..., ...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...)&, noexcept_state> { using type = R(Args...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const &, noexcept_state> { using type = R(Args...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile &, noexcept_state> { using type = R(Args...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile &, noexcept_state> { using type = R(Args...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...)&, noexcept_state> { using type = R(Args..., ...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const &, noexcept_state> { using type = R(Args..., ...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile &, noexcept_state> { using type = R(Args..., ...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile &, noexcept_state> { using type = R(Args..., ...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) &&, noexcept_state> { using type = R(Args...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const &&, noexcept_state> { using type = R(Args...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) volatile &&, noexcept_state> { using type = R(Args...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args...) const volatile &&, noexcept_state> { using type = R(Args...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) &&, noexcept_state> { using type = R(Args..., ...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const &&, noexcept_state> { using type = R(Args..., ...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) volatile &&, noexcept_state> { using type = R(Args..., ...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename... Args>
struct make_noexcept<R(Args..., ...) const volatile &&, noexcept_state> { using type = R(Args..., ...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...), noexcept_state> { using type = R(C::*)(Args...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const, noexcept_state> { using type = R(C::*)(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile, noexcept_state> { using type = R(C::*)(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile, noexcept_state> { using type = R(C::*)(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...), noexcept_state> { using type = R(C::*)(Args..., ...) noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const, noexcept_state> { using type = R(C::*)(Args...) const noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile, noexcept_state> { using type = R(C::*)(Args...) volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile, noexcept_state> { using type = R(C::*)(Args...) const volatile noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...)&, noexcept_state> { using type = R(C::*)(Args...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const &, noexcept_state> { using type = R(C::*)(Args...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile &, noexcept_state> { using type = R(C::*)(Args...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile &, noexcept_state> { using type = R(C::*)(Args...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...)&, noexcept_state> { using type = R(C::*)(Args..., ...) & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const &, noexcept_state> { using type = R(C::*)(Args..., ...) const & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile &, noexcept_state> { using type = R(C::*)(Args..., ...) volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile &, noexcept_state> { using type = R(C::*)(Args..., ...) const volatile & noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) &&, noexcept_state> { using type = R(C::*)(Args...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const &&, noexcept_state> { using type = R(C::*)(Args...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) volatile &&, noexcept_state> { using type = R(C::*)(Args...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args...) const volatile &&, noexcept_state> { using type = R(C::*)(Args...) const volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) &&, noexcept_state> { using type = R(C::*)(Args..., ...) && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const &&, noexcept_state> { using type = R(C::*)(Args..., ...) const && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) volatile &&, noexcept_state> { using type = R(C::*)(Args..., ...) volatile && noexcept(noexcept_state); };
template<bool noexcept_state, typename R, typename C, typename... Args>
struct make_noexcept<R(C::*)(Args..., ...) const volatile &&, noexcept_state> { using type = R(C::*)(Args..., ...) const volatile && noexcept(noexcept_state); };

template<typename T, bool noexcept_state = true>
using make_noexcept_t = typename make_noexcept<T, noexcept_state>::type;

template<typename T>
using remove_noexcept_t = make_noexcept_t<T, false>;
