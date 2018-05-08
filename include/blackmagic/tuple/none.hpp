#pragma once

#include "all.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

struct none_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return !all(tpl);
  }
};

inline constexpr none_t none{};

}} // namespace blackmagic::tuple::algorithm
