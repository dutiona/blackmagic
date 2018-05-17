#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct rotate_left_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    return push_back(pop_front(tpl), front(tpl));
  }
};

inline constexpr const rotate_left_t rotate_left{};

}} // namespace blackmagic::tuple::algorithm
