#pragma once

#include "../common/common.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

namespace details {

template <typename... Ts, typename... Us, size_t... I>
constexpr bool not_equal_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return common_helpers::any_of_v((std::get<I>(lhs) != std::get<I>(rhs))...);
}

} // namespace details

struct not_equals_t {
  template <typename... Ts, typename... Us>
  constexpr bool operator()(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs) const
  {
    if constexpr (sizeof...(Ts) != sizeof...(Us)) {
      return true;
    }
    else {
      return details::not_equal_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
    }
  }
};

inline constexpr not_equals_t not_equals{};

}} // namespace metaprog::tuple::algorithm
