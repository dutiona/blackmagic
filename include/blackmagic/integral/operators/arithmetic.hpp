#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/tag_of.hpp"
#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace arithmetic {

using common::_v;
using common::tag_of_t;

namespace {

template <typename Tag>
struct arithmetic_operators {
  static constexpr bool value = false;
};

template <>
struct arithmetic_operators<tags::char_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::short_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::int_tag> {
  static constexpr bool value = true;
};
template <>
struct arithmetic_operators<tags::long_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::long_long_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::unsigned_char_tag> {
  static constexpr bool value = true;
};
template <>
struct arithmetic_operators<tags::unsigned_short_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::unsigned_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::unsigned_int_tag> {
  static constexpr bool value = true;
};
template <>
struct arithmetic_operators<tags::unsigned_long_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::unsigned_long_long_tag> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<tags::size_t_tag> {
  static constexpr bool value = true;
};

} // namespace


// unary +
template <typename T, typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>>>>
constexpr decltype(auto) operator+(T&& t)
{
  return positive(std::forward<T>(t));
}

// unary -
template <typename T, typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>>>>
constexpr decltype(auto) operator-(T&& t)
{
  return negative(std::forward<T>(t));
}

// binary +
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator+(T&& t, U&& u)
{
  return plus(std::forward<T>(t), std::forward<U>(u));
}

// binary -
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator-(T&& t, U&& u)
{
  return minus(std::forward<T>(t), std::forward<U>(u));
}

// /
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator/(T&& t, U&& u)
{
  return div(std::forward<T>(t), std::forward<U>(u));
}

// *
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator*(T&& t, U&& u)
{
  return mult(std::forward<T>(t), std::forward<U>(u));
}

// %
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator%(T&& t, U&& u)
{
  return mod(std::forward<T>(t), std::forward<U>(u));
}

// ~
template <typename T, typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>>>>
constexpr decltype(auto) operator~(T&& t)
{
  return bit_not(std::forward<T>(t));
}

// &
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator&(T&& t, U&& u)
{
  return bit_and(std::forward<T>(t), std::forward<U>(u));
}

// |
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator|(T&& t, U&& u)
{
  return bit_or(std::forward<T>(t), std::forward<U>(u));
}

// ^
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator^(T&& t, U&& u)
{
  return bit_xor(std::forward<T>(t), std::forward<U>(u));
}

// <<
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator<<(T&& t, U&& u)
{
  return bit_lshift(std::forward<T>(t), std::forward<U>(u));
}

// >>
template <typename T, typename U,
          typename = std::enable_if_t<_v<arithmetic_operators<tag_of_t<T>>> || _v<arithmetic_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator>>(T&& t, U&& u)
{
  return bit_rshift(std::forward<T>(t), std::forward<U>(u));
}

}}} // namespace blackmagic::integral::operators::arithmetic
