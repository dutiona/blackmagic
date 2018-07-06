#pragma once

#include "../../functional/partial.hpp"
#include "../../functional/reverse_partial.hpp"
#include "../../common/utility.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct equal_t {
  template <typename... Ts, typename... Us>
  constexpr bool operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const;

  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& lhs) const;

  template <typename... Us>
  constexpr decltype(auto) to(const std::tuple<Us...>& rhs) const;
};

inline constexpr const equal_t equal{};

namespace details {

template <typename... Ts, typename... Us, size_t... I>
constexpr bool equal_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return common::all_of_v((std::get<I>(lhs) == std::get<I>(rhs))...);
}

} // namespace details


template <typename... Ts, typename... Us>
constexpr bool equal_t::operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const
{
  if constexpr (sizeof...(Ts) != sizeof...(Us)) {
    return false;
  }
  else {
    return details::equal_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
  }
}

// non owning
template <typename... Ts>
constexpr decltype(auto) equal_t::operator()(const std::tuple<Ts...>& lhs) const
{
  return functional::partial(equal, lhs);
}

template <typename... Us>
constexpr decltype(auto) equal_t::to(const std::tuple<Us...>& rhs) const
{
  return functional::reverse_partial(equal, rhs);
}

}} // namespace blackmagic::tuple::algorithm
