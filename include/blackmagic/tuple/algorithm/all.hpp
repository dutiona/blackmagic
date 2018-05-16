#pragma once

#include "all_of.hpp"

#include "../../functional/functional.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

namespace functional = blackmagic::functional;

struct all_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return all_of(tpl, functional::identity);
  }
};

inline constexpr all_t all{};

}} // namespace blackmagic::tuple::algorithm
