#pragma once

#include "../../integral/integral.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace integral = blackmagic::integral;

namespace details {

template <typename... Ts, size_t... I>
constexpr auto take_front_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<I>(tpl)...);
}

} // namespace details

struct take_front_t {
  template <size_t N, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, integral::size_t_<N>) const
  {
    if constexpr (N == 0) {
      return std::tuple<>();
    }
    else if constexpr (N >= sizeof...(Ts)) {
      return tpl;
    }
    else {
      return details::take_front_impl(tpl, std::make_index_sequence<N>{});
    }
  }
};

inline constexpr take_front_t take_front{};

}} // namespace blackmagic::tuple::algorithm
