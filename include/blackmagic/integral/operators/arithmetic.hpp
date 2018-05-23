#pragma once

#include "../utility.hpp"
#include "tag_of.hpp"
#include "traits.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace arithmetic {

namespace common = blackmagic::common;
using common::_t;
using trait::arithmetic_trait;
using trait::enable_trait;

namespace details {

template <template <auto...> class T>
inline constexpr const auto enabled_unary_plus_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::positive;

template <template <auto...> class T>
inline constexpr const auto enabled_unary_minus_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::negative;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_binary_plus_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::plus;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_binary_minus_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::minus;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_div_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::div;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_mult_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::mult;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_mod_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::mod;

template <template <auto...> class T>
inline constexpr const auto enabled_not_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::bit_not;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_or_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::bit_or;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_and_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::bit_and;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_xor_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::bit_xor;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_lshift_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::bit_lshift;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_rshift_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::bit_rshift;

} // namespace details


// unary +
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_unary_plus_v<T>>>
constexpr decltype(auto) operator+(T<Args...>&& t)
{
  return positive<T>(std::forward<T>(t));
}

// unary -
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_unary_minus_v<T>>>
constexpr decltype(auto) operator-(T<Args...>&& t)
{
  return negative<T>(std::forward<T>(t));
}

// binary +
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_binary_plus_v<T, U>>>
constexpr decltype(auto) operator+(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return plus<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// binary -
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_binary_minus_v<T, U>>>
constexpr decltype(auto) operator-(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return minus<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// /
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_div_v<T, U>>>
constexpr decltype(auto) operator/(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return div<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// *
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_mult_v<T, U>>>
constexpr decltype(auto) operator*(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return mult<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// %
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_mod_v<T, U>>>
constexpr decltype(auto) operator%(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return mod<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// ~
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_not_v<T>>>
constexpr decltype(auto) operator~(T<Args...>&& t)
{
  return bit_not<T>(std::forward<T>(t));
}

// &
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_or_v<T, U>>>
constexpr decltype(auto) operator&(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return bit_and<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// |
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_and_v<T, U>>>
constexpr decltype(auto) operator|(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return bit_or<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// ^
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_xor_v<T, U>>>
constexpr decltype(auto) operator^(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return bit_xor<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// <<
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_lshift_v<T, U>>>
constexpr decltype(auto) operator<<(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return bit_lshift<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// >>
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_rshift_v<T, U>>>
constexpr decltype(auto) operator>>(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return bit_rshift<T, U>(std::forward<T>(t), std::forward<U>(u));
}

}}} // namespace blackmagic::integral::operators::arithmetic
