#pragma once

#include "make_lazy.hpp"

namespace blackmagic::functional::lazy {

struct eval_t {
  template <typename Func, typename... Args>
  constexpr decltype(auto) operator()(const lazy_expr<Func, Args...>& fctor) const
  {
    return fctor();
  }
};

inline constexpr const eval_t eval{};

} // namespace blackmagic::functional::lazy
