#pragma once

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct back_t {
  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return std::get<(sizeof...(Ts) - 1)>(tpl);
  }
};

inline constexpr const back_t back{};

}} // namespace blackmagic::tuple::algorithm
