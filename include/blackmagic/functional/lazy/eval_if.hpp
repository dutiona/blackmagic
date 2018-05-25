#pragma once

#include "eval.hpp"
#include "make_lazy.hpp"

#include "../../common/detector.hpp"
#include "../../integral/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::functional::lazy {

namespace details {

template <typename T>
using value_type_t = typename T::value_type;

} // namespace details

struct eval_if_t {
  template <typename C, typename ThenFunc, typename... ThenArgs, typename ElseFunc, typename... ElseArgs>
  constexpr decltype(auto) operator()(C&& cond, const lazy_expr<ThenFunc, ThenArgs...>& then,
                                      const lazy_expr<ElseFunc, ElseArgs...>& else_) const
  {
    using Cond = std::decay_t<C>;
    if constexpr (std::is_convertible_v<Cond, bool> && !common::is_detected_v<details::value_type_t, Cond>) {
      if (cond) {
        return eval(then);
      }
      else {
        return eval(else_);
      }
    }
    else if constexpr (common::is_detected_v<details::value_type_t, Cond> && integral::is_bool_c_v<Cond>) {
      if constexpr (Cond()) {
        return eval(then);
      }
      else {
        return eval(else_);
      }
    }
    else {
      throw "Bad type for condition : only std::integral_constant::value_type == bool or integral convertible to bool "
            "allowed!";
    }
  }
};

inline constexpr const eval_if_t eval_if{};

} // namespace blackmagic::functional::lazy
