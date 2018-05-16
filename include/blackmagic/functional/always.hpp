#pragma once

#include <utility>

namespace blackmagic::functional {

struct always_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& value) const
  {
    return [v = std::forward<T>(value)](auto&&...) { return v; };
  }
};

inline constexpr const always_t always{};

} // namespace blackmagic::functional
