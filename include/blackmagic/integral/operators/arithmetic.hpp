#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace arithmetic {

using common::_v;


namespace {

template <typename Tag>
struct arithmetic_operators {
  static constexpr bool value = false;
};

template <>
struct arithmetic_operators<char> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<short> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<int> {
  static constexpr bool value = true;
};
template <>
struct arithmetic_operators<long> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<long long> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<unsigned char> {
  static constexpr bool value = true;
};
template <>
struct arithmetic_operators<unsigned short> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<unsigned> {
  static constexpr bool value = true;
};
/*
template <>
struct arithmetic_operators<unsigned int> {
  static constexpr bool value = true;
};*/

template <>
struct arithmetic_operators<unsigned long> {
  static constexpr bool value = true;
};

template <>
struct arithmetic_operators<unsigned long long> {
  static constexpr bool value = true;
};
/*
template <>
struct arithmetic_operators<size_t> {
  static constexpr bool value = true;
};*/

} // namespace


// unary +
template <typename T, auto V, typename = std::enable_if_t<_v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator+(const std::integral_constant<T, V>& t)
{
  return positive(t);
}

// unary -
template <typename T, auto V, typename = std::enable_if_t<_v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator-(const std::integral_constant<T, V>& t)
{
  return negative(t);
}

// binary +
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator+(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return plus(t, u);
}

// binary -
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator-(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return minus(t, u);
}

// /
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator/(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return div(t, u);
}

// *
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator*(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return mult(t, u);
}

// %
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator%(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return mod(t, u);
}

// ~
template <typename T, auto V, typename = std::enable_if_t<_v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator~(const std::integral_constant<T, V>& t)
{
  return bit_not(t);
}

// &
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator&(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return bit_and(t, u);
}

// |
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator|(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return bit_or(t, u);
}

// ^
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator^(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return bit_xor(t, u);
}

// <<
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator<<(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return bit_lshift(t, u);
}

// >>
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<arithmetic_operators<T>> || _v<arithmetic_operators<T>>>>
constexpr decltype(auto) operator>>(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return bit_rshift(t, u);
}

}}} // namespace blackmagic::integral::operators::arithmetic
