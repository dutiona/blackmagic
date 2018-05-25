#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_front.hpp"
#include "remove_if.hpp"

#include "../../common/traits_ext.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

// fwd decl
struct unique_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const;
};

inline constexpr const unique_t unique{};

namespace details {

template <typename... Ts, size_t... I>
constexpr auto unique_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  if constexpr (sizeof...(Ts) == 0) {
    return tpl;
  }
  else {
    return push_front(
      unique(remove_if(pop_front(tpl), common::trait<std::is_same, std::decay_t<decltype(front(tpl))>>)), front(tpl));
  }
}

} // namespace details

template <typename... Ts>
constexpr auto unique_t::operator()(const std::tuple<Ts...>& tpl) const
{
  return details::unique_impl(tpl, std::index_sequence_for<Ts...>{});
}

}} // namespace blackmagic::tuple::algorithm
