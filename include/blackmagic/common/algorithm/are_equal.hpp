#pragma once

namespace blackmagic::common { inline namespace algorithm {

// are_equal
struct are_equal_t {
  template <typename T, typename... Ts>
  constexpr bool operator()(T&& lhs, Ts&&... rhs) const
  {
    return ((lhs == rhs) && ...);
  }
};

inline constexpr const are_equal_t are_equal{};

}} // namespace blackmagic::common::algorithm
