#pragma once

#include "all_of.hpp"

#include "../common/common.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common_helpers = blackmagic::common::helpers;

struct all_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return all_of(tpl, common_helpers::identity_func);
  }
};

inline constexpr all_t all{};

}} // namespace blackmagic::tuple::algorithm
