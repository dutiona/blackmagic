#pragma once

#include "../utility.hpp"
#include "tag_of.hpp"
#include "traits.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace logical {

using common::_t;
using trait::enable_trait;
using trait::logical_trait;

namespace details {

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_and_v =
  logical_trait<(enable_trait<_t<tag_of<T>>>::logical || enable_trait<_t<tag_of<U>>>::logical), _t<tag_of<T>>,
                _t<tag_of<U>>>::logical_and;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_or_v =
  logical_trait<(enable_trait<_t<tag_of<T>>>::logical || enable_trait<_t<tag_of<U>>>::logical), _t<tag_of<T>>,
                _t<tag_of<U>>>::logical_or;

template <template <auto...> class T>
inline constexpr const auto enabled_not_v =
  logical_trait<enable_trait<_t<tag_of<T>>>::logical, _t<tag_of<T>>>::logical_not;

} // namespace details


// &&
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_and_v<T, U>>>
constexpr decltype(auto) operator&&(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return logical_and(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// ||
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_or_v<T, U>>>
constexpr decltype(auto) operator||(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return logical_or(std::forward<T<ArgsT...>>(t), std::forward<U<ArgsU...>>(u));
}

// !
template <template <auto...> class T, auto... Args, typename = std::enable_if_t<details::enabled_not_v<T>>>
constexpr decltype(auto) operator!(T<Args...>&& t)
{
  return logical_not(std::forward<T<Args...>>(t));
}

}}} // namespace blackmagic::integral::operators::logical
