#pragma once

#include "../../common/common.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common = blackmagic::common;

namespace details {

template <typename... Ts, typename... Us, size_t... I>
constexpr bool equals_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return common::all_of_v((std::get<I>(lhs) == std::get<I>(rhs))...);
}

} // namespace details

struct equals_t {
  template <typename... Ts, typename... Us>
  constexpr bool operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const
  {
    if constexpr (sizeof...(Ts) != sizeof...(Us)) {
      return false;
    }
    else {
      return details::equals_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
    }
  }
};

inline constexpr equals_t equals{};

}} // namespace blackmagic::tuple::algorithm
