#pragma once

#include "all_of.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct none_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return !all_of(tpl, std::forward<Func>(f));
  }
};

inline constexpr const none_of_t none_of{};

}} // namespace blackmagic::tuple::algorithm
