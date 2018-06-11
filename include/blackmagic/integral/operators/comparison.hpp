#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace comparison {

using common::_v;

namespace {

template <typename Tag>
struct comparison_operators {
  static constexpr bool value = false;
};

template <>
struct comparison_operators<bool> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<char> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<short> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<int> {
  static constexpr bool value = true;
};
template <>
struct comparison_operators<long> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<long long> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<unsigned char> {
  static constexpr bool value = true;
};
template <>
struct comparison_operators<unsigned short> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<unsigned> {
  static constexpr bool value = true;
};

/*
template <>
struct comparison_operators<unsigned int> {
  static constexpr bool value = true;
};*/

template <>
struct comparison_operators<unsigned long> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<unsigned long long> {
  static constexpr bool value = true;
};

/*
template <>
struct comparison_operators<size_t> {
  static constexpr bool value = true;
};*/

} // namespace


// ==
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> && _v<comparison_operators<U>>>>
constexpr decltype(auto) operator==(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return equal(t, u);
}

// !=
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> || _v<comparison_operators<U>>>>
constexpr decltype(auto) operator!=(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return not_equal(t, u);
}

// <
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> || _v<comparison_operators<U>>>>
constexpr decltype(auto) operator<(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return less(t, u);
}

// <=
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> || _v<comparison_operators<U>>>>
constexpr decltype(auto) operator<=(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return less_equal(t, u);
}

// >
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> || _v<comparison_operators<U>>>>
constexpr decltype(auto) operator>(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return greater(t, u);
}

// >=
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<comparison_operators<T>> || _v<comparison_operators<U>>>>
constexpr decltype(auto) operator>=(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return greater_equal(t, u);
}

}}} // namespace blackmagic::integral::operators::comparison
