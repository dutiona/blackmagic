#pragma once

#ifndef METAPROG_COMMON_HELPERS_HPP
#define METAPROG_COMMON_HELPERS_HPP

#include "../type/type.hpp"

#ifdef __GLIBCXX__
#include "../ctx/ctx.hpp"
#endif // __GLIBCXX__

#include <functional>
#include <string_view>
#include <type_traits>

namespace common {

// nonesuch

struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(const nonesuch&) = delete;
  void operator=(const nonesuch&) = delete;
};

// is_detected

namespace details {

template <typename Default, template <typename...> class Op, typename ParametersPack, typename = void>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <typename Default, template <typename...> class Op, template <typename...> class ParametersPack,
  typename... Args>
struct detector<Default, Op, ParametersPack<Args...>, std::void_t<Op<Args...>>> {
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <typename...> class Op, typename... Args>
using is_detected = typename details::detector<nonesuch, Op, type::basic_type_holder<Args...>>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = typename details::detector<nonesuch, Op, type::basic_type_holder<Args...>>::type;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = details::detector<Default, Op, type::basic_type_holder<Args...>>;

template <template <typename...> class Op, typename... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

template <typename Expected, template <typename...> class Op, typename... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <typename Expected, template <typename...> class Op, typename... Args>
constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

template <typename To, template <typename...> class Op, typename... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template <typename To, template <typename...> class Op, typename... Args>
constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;


// invoke_result

namespace details {

template <typename AlwaysVoid, typename, typename...>
struct invoke_result {
};
template <typename F, typename... Args>
struct invoke_result<decltype(void(std::invoke(std::declval<F>(), std::declval<Args>()...))), F, Args...> {
  using type = decltype(std::invoke(std::declval<F>(), std::declval<Args>()...));
};

} // namespace details

template <typename F, typename... Args>
struct invoke_result : details::invoke_result<void, F, Args...> {
};
template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;


// dependent false
template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool()
  {
    return value;
  }
};

template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});

// operator==(string_view, string_view) is not constexpr yet in libstdc++
constexpr bool equals(std::string_view lhs, std::string_view rhs)
{
#ifdef __GLIBCXX__
  return ctx::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
#else
  return lhs == rhs;
#endif // __GLIBCXX__
}


// all_of / any_of / none_of / count constexpr
// TODO/FIXME remove this once fold expression are implemented
template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr>
constexpr bool all_of(T b)
{
  return b;
}
template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr, typename... Ts>
constexpr bool all_of(T b, Ts... bools)
{
  return b && all_of(bools...);
}

template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr>
constexpr bool any_of(T b)
{
  return b;
}
template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr, typename... Ts>
constexpr bool any_of(T b, Ts... bools)
{
  return b || any_of(bools...);
}

template <typename... Ts>
constexpr bool none_of(Ts... bools)
{
  return !all_of(bools...);
}

template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr>
constexpr size_t count(T b)
{
  return b;
}
template <typename T, std::enable_if_t<std::is_convertible_v<T, bool>, void>* = nullptr, typename... Ts>
constexpr size_t count(T b, Ts... bools)
{
  return b + count(bools...);
}

} // namespace common


#endif // METAPROG_COMMON_HELPERS_HPP
