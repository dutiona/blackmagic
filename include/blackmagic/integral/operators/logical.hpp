#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/tag_of.hpp"
#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace logical {

using common::_v;
using common::tag_of_t;

namespace {

template <typename Tag>
struct logical_operators {
  static constexpr bool value = false;
};

template <>
struct logical_operators<tags::bool_tag> {
  static constexpr bool value = true;
};

} // namespace


// &&
template <typename T, typename U,
          typename = std::enable_if_t<_v<logical_operators<tag_of_t<T>>> || _v<logical_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator&&(T&& t, U&& u)
{
  return logical_and(std::forward<T>(t), std::forward<U>(u));
}

// ||
template <typename T, typename U,
          typename = std::enable_if_t<_v<logical_operators<tag_of_t<T>>> || _v<logical_operators<tag_of_t<U>>>>>
constexpr decltype(auto) operator||(T&& t, U&& u)
{
  return logical_or(std::forward<T>(t), std::forward<U>(u));
}

// !
template <typename T, typename = std::enable_if_t<_v<logical_operators<tag_of_t<T>>>>>
constexpr decltype(auto) operator!(T&& t)
{
  return logical_not(std::forward<T>(t));
}

}}} // namespace blackmagic::integral::operators::logical
