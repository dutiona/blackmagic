#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::common { inline namespace algorithm {

// count_v
struct count_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... nbs) const
  {
    static_assert((std::is_convertible_v<Ts, size_t> && ...), "Arguments not convertible to size_t.");
    return (nbs + ...);
  }
};

inline constexpr const count_v_t count_v{};

}} // namespace blackmagic::common::algorithm
