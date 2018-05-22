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
inline constexpr const auto enabled_incr_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::incr;

template <template <auto...> class T>
inline constexpr const auto enabled_decr_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::decr;

template <template <auto...> class T>
inline constexpr const auto enabled_unary_plus_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::unary_plus;

template <template <auto...> class T>
inline constexpr const auto enabled_unary_minus_v =
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::unary_minus;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_binary_plus_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::binary_plus;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_binary_minus_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::binary_minus;

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
  arithmetic_trait<enable_trait<_t<tag_of<T>>>::arithmetic, _t<tag_of<T>>>::Not;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_or_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::Or;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_and_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::And;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_xor_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::Xor;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_lshift_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::lshift;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_rshift_v =
  arithmetic_trait<(enable_trait<_t<tag_of<T>>>::arithmetic || enable_trait<_t<tag_of<U>>>::arithmetic), _t<tag_of<T>>,
                   _t<tag_of<U>>>::rshift;

} // namespace details


// ==


// ++
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_incr_v<T>>>
constexpr decltype(auto) operator++(T<Args...>&& t)
{
  return incr<T>(std::forward<T>(t));
}

// --
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_decr_v<T>>>
constexpr decltype(auto) operator--(T<Args...>&& t)
{
  return decr<T>(std::forward<T>(t));
}

// unary +
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_unary_plus_v<T>>>
constexpr decltype(auto) operator+(T<Args...>&& t)
{
  return unary_plus<T>(std::forward<T>(t));
}

// unary -
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_unary_minus_v<T>>>
constexpr decltype(auto) operator-(T<Args...>&& t)
{
  return unary_minus<T>(std::forward<T>(t));
}

// binary +
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_binary_plus_v<T, U>>>
constexpr decltype(auto) operator+(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return binary_plus<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// binary -
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_binary_minus_v<T, U>>>
constexpr decltype(auto) operator-(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return binary_minus<T, U>(std::forward<T>(t), std::forward<U>(u));
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
  return Not<T>(std::forward<T>(t));
}

// &
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_or_v<T, U>>>
constexpr decltype(auto) operator&(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return And<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// |
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_and_v<T, U>>>
constexpr decltype(auto) operator|(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return Or<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// ^
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_xor_v<T, U>>>
constexpr decltype(auto) operator^(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return Xor<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// <<
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_lshift_v<T, U>>>
constexpr decltype(auto) operator<<(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return lshift<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// >>
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_rshift_v<T, U>>>
constexpr decltype(auto) operator>>(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return rshift<T, U>(std::forward<T>(t), std::forward<U>(u));
}

}}} // namespace blackmagic::integral::operators::arithmetic
