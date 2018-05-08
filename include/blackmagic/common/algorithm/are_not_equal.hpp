#pragma once

namespace blackmagic::common { inline namespace algorithm {

// are_not_equal
struct are_not_equal_t {
  template <typename T, typename... Ts>
  constexpr bool operator()(T&& lhs, Ts&&... rhs) const
  {
    return ((lhs != rhs) && ...);
  }
};

inline constexpr are_not_equal_t are_not_equal{};

}} // namespace blackmagic::common::algorithm
