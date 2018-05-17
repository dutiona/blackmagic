#pragma once

#include "all.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct none_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return !all(tpl);
  }
};

inline constexpr const none_t none{};

}} // namespace blackmagic::tuple::algorithm
