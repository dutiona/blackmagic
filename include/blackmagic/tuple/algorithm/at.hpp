#pragma once

#include "../../common/common.hpp"

#include <tuple>
#include <type_traits>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common = blackmagic::common;

struct at_t {
  template <typename... Ts, typename N>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl, N) const
  {
    static_assert(std::is_base_of_v<std::integral_constant, common::remove_cvref_t<N>>,
                  "Index must be an integral constant!");
    static_assert(N::value < sizeof...(Ts) && N::value >= 0, "Index out of range!");

    return std::get<N::value>(tpl);
  }
};

inline constexpr at_t at{};

}} // namespace blackmagic::tuple::algorithm
