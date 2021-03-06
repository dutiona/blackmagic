#pragma once

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct end_t {
  template <typename... Ts>
  constexpr size_t operator()(const std::tuple<Ts...>&) const
  {
    return std::tuple_size_v<std::tuple<Ts...>>;
  }
};

inline constexpr const end_t end{};

}} // namespace blackmagic::tuple::algorithm
