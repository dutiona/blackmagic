#pragma once

#include "../utility.hpp"
#include "tag_of.hpp"
#include "traits.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace operators { inline namespace comparison {

namespace common = blackmagic::common;
using common::_t;
using trait::comparison_trait;
using trait::enable_trait;

namespace details {

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_equal_to_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::equal_to;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_not_equal_to_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::not_equal_to;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_less_than_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::less_than;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_less_equal_than_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::less_equal_than;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_greater_than_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::greater_than;

template <template <auto...> class T, template <auto...> class U>
inline constexpr const auto enabled_greater_equal_than_v =
  comparison_trait<(enable_trait<_t<tag_of<T>>>::comparison || enable_trait<_t<tag_of<U>>>::comparison), _t<tag_of<T>>,
                   _t<tag_of<U>>>::greater_equal_than;

} // namespace details


// ==
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_equal_to_v<T, U>>>
constexpr decltype(auto) operator==(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return equal_to<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// !=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_not_equal_to_v<T, U>>>
constexpr decltype(auto) operator!=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return not_equal_to<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// <
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_less_than_v<T, U>>>
constexpr decltype(auto) operator<(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return less_than<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// <=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_less_equal_than_v<T, U>>>
constexpr decltype(auto) operator<=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return less_equal_than<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// >
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_greater_than_v<T, U>>>
constexpr decltype(auto) operator>(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return greater_than<T, U>(std::forward<T>(t), std::forward<U>(u));
}

// >=
template <template <auto...> class T, template <auto...> class U, auto... ArgsT, auto... ArgsU,
          typename = std::enable_if_t<details::enabled_greater_equal_than_v<T, U>>>
constexpr decltype(auto) operator>=(T<ArgsT...>&& t, U<ArgsU...>&& u)
{
  return greater_equal_than<T, U>(std::forward<T>(t), std::forward<U>(u));
}

}}} // namespace blackmagic::integral::operators::comparison
