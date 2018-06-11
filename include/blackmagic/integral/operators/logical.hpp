#pragma once

#include "../functors.hpp"
#include "../types.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace logical {

using common::_v;

namespace {

template <typename Tag>
struct logical_operators {
  static constexpr bool value = false;
};

template <>
struct logical_operators<bool> {
  static constexpr bool value = true;
};

} // namespace


// &&
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<logical_operators<T>> || _v<logical_operators<U>>>>
constexpr decltype(auto) operator&&(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return logical_and(t, u);
}

// ||
template <typename T, auto V, typename U, auto W,
          typename = std::enable_if_t<_v<logical_operators<T>> || _v<logical_operators<U>>>>
constexpr decltype(auto) operator||(const std::integral_constant<T, V>& t, const std::integral_constant<U, W>& u)
{
  return logical_or(t, u);
}

// !
template <typename T, auto V, typename = std::enable_if_t<_v<logical_operators<T>>>>
constexpr decltype(auto) operator!(const std::integral_constant<T, V>& t)
{
  return logical_not(t);
}


}}} // namespace blackmagic::integral::operators::logical
