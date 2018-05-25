#pragma once

#include "transform.hpp"
#include "unpack.hpp"

#include "../../common/algorithm/any_of_v.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct any_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return unpack(transform(tpl, std::forward<Func>(f)), common::any_of_v);
  }
};

inline constexpr const any_of_t any_of{};

}} // namespace blackmagic::tuple::algorithm
