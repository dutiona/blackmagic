#pragma once

#include <utility>

namespace blackmagic::functional {

struct apply_t {
  template <typename Func, typename... Args>
  constexpr decltype(auto) operator()(Func&& f, Args&&... args) const
  {
    return std::forward<Func>(f)(std::forward<Args>(args)...);
  }
};

inline constexpr const apply_t apply{};

} // namespace blackmagic::functional
