#pragma once

#include "helpers.hpp"
#include "transform.hpp"
#include "unpack.hpp"

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

struct any_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return unpack(transform(tpl, std::forward<Func>(f)), common_helpers::any_of_v);
  }

  template <typename... Ts>
  constexpr bool operator()(const std::tuple<Ts...>& tpl) const
  {
    return operator()(tpl, common_helpers::identity_func);
  }
};

inline constexpr any_of_t any_of{};

}} // namespace metaprog::tuple::algorithm
