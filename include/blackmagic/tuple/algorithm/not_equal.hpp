#pragma once

#include "../../common/utility.hpp"
#include "../../functional/partial.hpp"
#include "../../functional/reverse_partial.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct not_equal_t {
  template <typename... Ts, typename... Us>
  constexpr bool operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const;

  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& lhs) const;

  template <typename... Us>
  constexpr bool to(const std::tuple<Us...>& rhs) const;
};

inline constexpr const not_equal_t not_equal{};

namespace details {

template <typename... Ts, typename... Us, size_t... I>
constexpr bool not_equal_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return common::any_of_v((std::get<I>(lhs) != std::get<I>(rhs))...);
}

} // namespace details

template <typename... Ts, typename... Us>
constexpr bool not_equal_t::operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const
{
  if constexpr (sizeof...(Ts) != sizeof...(Us)) {
    return true;
  }
  else {
    return details::not_equal_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
  }
}

template <typename... Ts>
constexpr bool not_equal_t::operator()(const std::tuple<Ts...>& lhs) const
{
  return functional::partial(not_equal, lhs);
}

template <typename... Us>
constexpr bool not_equal_t::to(const std::tuple<Us...>& rhs) const
{
  return functional::reverse_partial(not_equal, rhs);
}


}} // namespace blackmagic::tuple::algorithm
