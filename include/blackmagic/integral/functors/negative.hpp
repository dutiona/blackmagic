#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct negative_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return negative_t<T>{};
  }
};

inline constexpr negative_functor_t negative{};

}}} // namespace blackmagic::integral::functors::arithmetic
