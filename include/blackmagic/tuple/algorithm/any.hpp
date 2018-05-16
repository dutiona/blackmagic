#pragma once

#include "any_of.hpp"

#include "../../functional/functional.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

namespace functional = blackmagic::functional;

struct any_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return any_of(tpl, functional::identity);
  }
};

inline constexpr any_t any{};

}} // namespace blackmagic::tuple::algorithm
