#pragma once

#include "eval.hpp"
#include "make_lazy.hpp"

namespace blackmagic::functional::lazy {

namespace tuple = blackmagic::tuple;

namespace details {
}

struct eval_if_t {
  template <typename T, typename ThenFunc, typename... ThenArgs, typename ElseFunc, typename... ElseArgs>
  constexpr decltype(auto) operator()(T&& cond, const lazy_expr<ThenFunc, ThenArgs...>& then,
                                      const lazy_expr<ElseFunc, ElseArgs...>& else_) const
  {
    if (cond) {
      return eval(then);
    }
    else {
      return eval(else_);
    }
  }
};

inline constexpr const eval_if_t eval_if{};

} // namespace blackmagic::functional::lazy
