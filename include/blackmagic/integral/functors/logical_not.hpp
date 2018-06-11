#pragma once

#include "../utility.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace logical {

struct logical_not_functor_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return logical_not_t<common::remove_cvref_t<T>>{};
  }
};

inline constexpr logical_not_functor_t logical_not{};

}}} // namespace blackmagic::integral::functors::logical
