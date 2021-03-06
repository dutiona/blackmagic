#pragma once

#include "all_of.hpp"

#include "../../functional/identity.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct all_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return all_of(tpl, functional::identity);
  }
};

inline constexpr const all_t all{};

}} // namespace blackmagic::tuple::algorithm
