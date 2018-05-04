#pragma once

#include "integral_types.hpp"

namespace metaprog::type {

using npos = size_t_<size_t(-1)>;

template <typename... Ts>
struct basic_list {
  static constexpr size_t size() noexcept
  {
    return sizeof...(Ts);
  }
};

} // namespace metaprog::type
