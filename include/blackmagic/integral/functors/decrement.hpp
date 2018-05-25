#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct decrement_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return decrement_t<T>{};
  }
};

inline constexpr decrement_functor_t decrement{};

}}} // namespace blackmagic::integral::functors::arithmetic
