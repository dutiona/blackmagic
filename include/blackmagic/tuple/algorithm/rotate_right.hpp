#pragma once

#include "back.hpp"
#include "pop_back.hpp"
#include "push_front.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct rotate_right_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    return push_front(pop_back(tpl), back(tpl));
  }
};

inline constexpr const rotate_right_t rotate_right{};

}} // namespace blackmagic::tuple::algorithm
