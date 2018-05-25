#pragma once

#include "merge.hpp"

#include "../../common/traits_ext.hpp"
#include "../../integral/types.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

using common::_v;

// fwd dcl
struct sort_t {
  template <typename C, typename... Ts>
  constexpr auto operator()(C&& comp, const std::tuple<Ts...>& tpl) const;
};

inline constexpr const sort_t sort{};

namespace details {

template <size_t N, size_t... I>
constexpr auto translate_index_sequence(std::index_sequence<I...>, integral::size_t_t<N>)
{
  return std::index_sequence<(I + N)...>{};
}

template <typename C, typename... Ts, size_t... I, size_t... J>
constexpr auto sort_impl(C&& comp, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, std::index_sequence<J...>)
{
  return merge(std::forward<C>(comp), sort(std::forward<C>(comp), std::make_tuple(std::get<I>(tpl)...)),
               sort(std::forward<C>(comp), std::make_tuple(std::get<J>(tpl)...)));
}

} // namespace details

template <typename C, typename... Ts>
constexpr auto sort_t::operator()(C&& comp, const std::tuple<Ts...>& tpl) const
{
  if constexpr (sizeof...(Ts) < 2) {
    return tpl;
  }
  else {
    using Pivot = integral::size_t_t<(sizeof...(Ts) / 2)>;
    return details::sort_impl(
      std::forward<C>(comp), tpl, std::make_index_sequence<_v<Pivot>>{},
      details::translate_index_sequence(std::make_index_sequence<(sizeof...(Ts) - _v<Pivot>)>{}, Pivot{}));
  }
}


}} // namespace blackmagic::tuple::algorithm
