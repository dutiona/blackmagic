#pragma once

#include <type_traits>

namespace blackmagic::common {

template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool() const
  {
    return value;
  }
};

template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});

} // namespace blackmagic::common
