#pragma once

#include "../utility.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct decrement_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return decrement_t<common::remove_cvref_t<T>>{};
  }
};

inline constexpr decrement_functor_t decrement{};

}}} // namespace blackmagic::integral::functors::arithmetic
