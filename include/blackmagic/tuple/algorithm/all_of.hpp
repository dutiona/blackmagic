#pragma once

#include "transform.hpp"
#include "unpack.hpp"

#include "../../common/common.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common = blackmagic::common;

struct all_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return unpack(transform(tpl, std::forward<Func>(f)), common::all_of_v);
  }
};

inline constexpr all_of_t all_of{};

}} // namespace blackmagic::tuple::algorithm
