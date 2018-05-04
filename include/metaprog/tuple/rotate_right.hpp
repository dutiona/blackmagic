#pragma once

#include "back.hpp"
#include "pop_back.hpp"
#include "push_front.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

struct rotate_right_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    return push_front(pop_back(tpl), back(tpl));
  }
};

} // namespace details

inline constexpr details::rotate_right_t rotate_right{};

}} // namespace metaprog::tuple::algorithm
