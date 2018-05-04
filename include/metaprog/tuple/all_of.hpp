#pragma once

#include "helpers.hpp"
#include "transform.hpp"
#include "unpack.hpp"

#include "../common/common.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

namespace details {

struct all_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return unpack(transform(tpl, std::forward<Func>(f)), common_helpers::all_of_v);
  }

  template <typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl) const
  {
    return operator()(tpl, helpers::identity_func);
  }
};

} // namespace details

inline constexpr details::all_of_t all_of{};

}} // namespace metaprog::tuple::algorithm
