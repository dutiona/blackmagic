#pragma once

#include "push_front.hpp"

#include "../../integral/types.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace integral = blackmagic::integral;

struct repeat_t {
  template <typename T, size_t N>
  constexpr auto operator()(T&& e, integral::size_t_<N>) const;
};

inline constexpr repeat_t repeat{};

template <typename T, size_t N>
constexpr auto repeat_t::operator()(T&& e, integral::size_t_<N>) const
{
  if constexpr (N == 0) {
    return std::make_tuple();
  }
  else {
    return push_front(repeat(std::forward<T>(e), integral::size_t_<(N - 1)>{}), std::forward<T>(e));
  }
}

}} // namespace blackmagic::tuple::algorithm
