#pragma once

#include "merge.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;
namespace type           = metaprog::type;

// fwd dcl
struct sort_t {
  template <typename C, typename... Ts>
  constexpr auto operator()(C&& comp, const std::tuple<Ts...>& tpl) const;
};

inline constexpr sort_t sort{};

namespace details {

template <size_t N, size_t... I>
constexpr auto translate_index_sequence(std::index_sequence<I...>)
{
  return std::index_sequence<(I + N)...>{};
};

template <typename C, typename... Ts, size_t... I, size_t... J>
constexpr auto sort_impl(C&& comp, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, std::index_sequence<J...>)
{
  return merge(std::forward<C>(comp), sort(std::forward<C>(comp), std::make_tuple(std::get<I>(tpl)...)),
               sort(std::forward<C>(comp), std::make_tuple(std::get<J>(tpl)...)));
};

} // namespace details

template <typename C, typename... Ts>
constexpr auto sort_t::operator()(C&& comp, const std::tuple<Ts...>& tpl) const
{
  if constexpr (sizeof...(Ts) < 2) {
    return tpl;
  }
  else {
    constexpr size_t pivot = sizeof...(Ts) / 2;
    return details::sort_impl(
      std::forward<C>(comp), tpl, std::make_index_sequence<pivot>{},
      details::translate_index_sequence<pivot>(std::make_index_sequence<sizeof...(Ts) - pivot>{}));
  }
}

}} // namespace metaprog::tuple::algorithm
