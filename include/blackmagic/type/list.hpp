#pragma once

#include "../integral/literals.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type {

using namespace integral::literals;

inline constexpr auto npos = -1_c;

template <typename... Ts>
struct basic_type_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

template <auto... Vs>
struct basic_value_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Vs);
  }
};

} // namespace blackmagic::type
