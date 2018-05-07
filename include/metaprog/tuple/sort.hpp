#pragma once

#include "merge.hpp"

#include "../type/type.hpp"

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
constexpr auto translate_index_sequence(std::index_sequence<I...>, type::size_t_<N>)
{
  return std::index_sequence<type::plus<type::size_t_<I>, type::size_t_<N>>::value...>{};
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
    using Pivot = type::size_t_<type::divides<type::size_t_<sizeof...(Ts)>, type::size_t_<2>>::value>;
    return details::sort_impl(
      std::forward<C>(comp), tpl, std::make_index_sequence<Pivot::value>{},
      details::translate_index_sequence(
        std::make_index_sequence<type::minus<type::size_t_<sizeof...(Ts)>, Pivot>::value>{}, Pivot{}));
  }
}

}} // namespace metaprog::tuple::algorithm
