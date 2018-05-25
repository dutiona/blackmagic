#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/tag_of.hpp"
#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace comparison {

using common::_v;
using common::tag_of_t;

namespace {

template <typename Tag>
struct comparison_operators {
  static constexpr bool value = false;
};

template <>
struct comparison_operators<tags::bool_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::char_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::short_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::int_tag> {
  static constexpr bool value = true;
};
template <>
struct comparison_operators<tags::long_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::long_long_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::unsigned_char_tag> {
  static constexpr bool value = true;
};
template <>
struct comparison_operators<tags::unsigned_short_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::unsigned_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::unsigned_int_tag> {
  static constexpr bool value = true;
};
template <>
struct comparison_operators<tags::unsigned_long_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::unsigned_long_long_tag> {
  static constexpr bool value = true;
};

template <>
struct comparison_operators<tags::size_t_tag> {
  static constexpr bool value = true;
};

} // namespace


// ==
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator==(T&& t, U&& u)
{
  return equal(std::forward<T>(t), std::forward<U>(u));
}

// !=
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator!=(T&& t, U&& u)
{
  return not_equal(std::forward<T>(t), std::forward<U>(u));
}

// <
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator<(T&& t, U&& u)
{
  return less(std::forward<T>(t), std::forward<U>(u));
}

// <=
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator<=(T&& t, U&& u)
{
  return less_equal(std::forward<T>(t), std::forward<U>(u));
}

// >
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator>(T&& t, U&& u)
{
  return greater(std::forward<T>(t), std::forward<U>(u));
}

// >=
template <typename T, typename U,
          typename = std::enable_if_t<_v<comparison_operators<tag_of_t<T>>> || _v<comparison_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator>=(T&& t, U&& u)
{
  return greater_equal(std::forward<T>(t), std::forward<U>(u));
}

}}} // namespace blackmagic::integral::operators::comparison
