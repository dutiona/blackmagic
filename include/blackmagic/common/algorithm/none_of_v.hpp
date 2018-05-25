#pragma once

#include "all_of_v.hpp"

#include <type_traits>

namespace blackmagic::common { inline namespace algorithm {

// none_of_v
struct none_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return !all_of_v(bools...);
  }
};

inline constexpr const none_of_v_t none_of_v{};

}} // namespace blackmagic::common::algorithm
