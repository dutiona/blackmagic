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

struct count_t {
  template <typename Func, typename... Ts>
  constexpr size_t operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return unpack(transform(tpl, std::forward<Func>(f)), common_helpers::count_v);
  }

  template <typename... Ts>
  constexpr size_t operator()(std::tuple<Ts...> tpl) const
  {
    return operator()(tpl, helpers::identity_func);
  }
};

inline constexpr count_t count{};

}} // namespace metaprog::tuple::algorithm
