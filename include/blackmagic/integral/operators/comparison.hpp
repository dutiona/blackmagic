#pragma once

#include "../utility.hpp"
#include "tag_of.hpp"
#include "traits.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace comparison {

using common::_t;
using trait::comparison_trait;
using trait::enable_trait;

namespace details {

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_equal_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::equal;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_not_equal_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::not_equal;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_less_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::less;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_less_equal_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::less_equal;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_greater_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::greater;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_greater_equal_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::greater;

} // namespace details


// ==
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_equal_v<T, U>>>
constexpr decltype(auto) operator==(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return equal(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// !=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_not_equal_v<T, U>>>
constexpr decltype(auto) operator!=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return not_equal(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// <
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_less_v<T, U>>>
constexpr decltype(auto) operator<(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return less(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// <=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_less_equal_v<T, U>>>
constexpr decltype(auto) operator<=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return less_equal(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// >
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_greater_v<T, U>>>
constexpr decltype(auto) operator>(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return greater(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// >=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_greater_equal_v<T, U>>>
constexpr decltype(auto) operator>=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return greater_equal(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

}}} // namespace blackmagic::integral::operators::comparison
