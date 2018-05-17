#pragma once

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct length_t {
  template <typename... Ts>
  constexpr size_t operator()(const std::tuple<Ts...>&) const
  {
    return std::tuple_size_v<std::tuple<Ts...>>;
  }
};

inline constexpr const length_t length{};

}} // namespace blackmagic::tuple::algorithm
