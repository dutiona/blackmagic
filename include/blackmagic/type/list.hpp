#pragma once

#include "../integral/integral.hpp"

namespace blackmagic::type {

namespace integral = blackmagic::integral;

using npos = integral::size_t_<size_t(-1)>;

template <typename... Ts>
struct basic_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

} // namespace blackmagic::type
