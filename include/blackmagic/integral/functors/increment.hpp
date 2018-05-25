#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct increment_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return increment_t<T>{};
  }
};

inline constexpr increment_functor_t increment{};

}}} // namespace blackmagic::integral::functors::arithmetic
