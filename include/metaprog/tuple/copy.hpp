#pragma once

#include "copy_if.hpp"

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

struct copy_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& value) const
  {
    return copy_if(tpl, common_helpers::trait<std::is_same, std::decay_t<decltype(std::forward<T>(value))>>);
  }
};

inline constexpr copy_t copy{};

}} // namespace metaprog::tuple::algorithm
