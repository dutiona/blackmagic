#pragma once

#include "reverse.hpp"
#include "take_front.hpp"

#include "../../integral/types.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

struct take_back_t {
  template <size_t N, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, integral::size_t_t<N> idx) const
  {
    return take_front(reverse(tpl), idx);
  }
};

inline constexpr const take_back_t take_back{};

}} // namespace blackmagic::tuple::algorithm
