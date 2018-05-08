#pragma once

#include <type_traits>

namespace blackmagic::common { inline namespace algorithm {

// all_of_v
struct all_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return (bools && ...);
  }
};

inline constexpr all_of_v_t all_of_v{};

}} // namespace blackmagic::common::algorithm
