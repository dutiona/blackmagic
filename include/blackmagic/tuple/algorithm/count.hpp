#pragma once

#include "count_if.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct count_t {
  template <typename... Ts, typename U>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const U& value) const
  {
    return count_if(tpl, [v = value](auto&& e) { return e == v; });
  }
};

inline constexpr count_t count{};

}} // namespace blackmagic::tuple::algorithm
