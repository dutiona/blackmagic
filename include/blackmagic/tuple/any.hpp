#pragma once

#include "any_of.hpp"

#include "../common/common.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common_helpers = blackmagic::common::helpers;

struct any_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return any_of(tpl, common_helpers::identity_func);
  }
};

inline constexpr any_t any{};

}} // namespace blackmagic::tuple::algorithm
