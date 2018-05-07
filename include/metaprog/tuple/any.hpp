#pragma once

#include "any_of.hpp"

#include "../common/common.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

struct any_t {
  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return any_of(tpl, common_helpers::identity_func);
  }
};

inline constexpr any_t any{};

}} // namespace metaprog::tuple::algorithm
