#pragma once

#include "../integral/types.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type {

namespace integral = blackmagic::integral;

// FIXME use -1_c when implemented
using npos = integral::long_long_t<-1>;

template <typename... Ts>
struct basic_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

} // namespace blackmagic::type
