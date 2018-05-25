#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct positive_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return positive_t<T>{};
  }
};

inline constexpr positive_functor_t positive{};

}}} // namespace blackmagic::integral::functors::arithmetic
