#pragma once

#include "count_if.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

struct count_t {
  template <typename... Ts, typename U>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const U& value) const
  {
    return count_if(tpl, [v = value](auto&& e) { return e == v; });
  }
};

inline constexpr count_t count{};

}} // namespace metaprog::tuple::algorithm
