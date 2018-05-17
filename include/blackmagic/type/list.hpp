#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::type {

using npos = std::integral_constant<int, -1>;

template <typename... Ts>
struct basic_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

} // namespace blackmagic::type
