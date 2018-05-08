#pragma once

#include "reverse.hpp"
#include "take_front.hpp"

#include "../type/type.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct take_back_t {
  template <size_t N, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, type::size_t_<N> idx) const
  {
    return take_front(reverse(tpl), idx);
  }
};

inline constexpr take_back_t take_back{};

}} // namespace blackmagic::tuple::algorithm
