#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct bit_not_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return bit_not_t<T>{};
  }
};

inline constexpr bit_not_functor_t bit_not{};

}}} // namespace blackmagic::integral::functors::arithmetic
