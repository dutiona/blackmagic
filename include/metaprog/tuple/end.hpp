#pragma once

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

struct end_t {
  template <typename... Ts>
  constexpr size_t operator()(const std::tuple<Ts...>&) const
  {
    return std::tuple_size_v<std::tuple<Ts...>>;
  }
};

inline constexpr end_t end{};

}} // namespace metaprog::tuple::algorithm
