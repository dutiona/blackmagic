#pragma once

#include <utility>

namespace blackmagic::functional {

struct identity_func_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    return std::forward<T>(t);
  }
};

inline constexpr const identity_func_t identity_func{};

} // namespace blackmagic::functional
