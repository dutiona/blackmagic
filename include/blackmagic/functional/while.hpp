#pragma once

#include "../integral/traits_ext.hpp"

#include <type_traits>
#include <utility>

namespace blackmagic::functional {

struct while_t {
  template <typename Pred, typename State, typename Func>
  constexpr decltype(auto) operator()(Pred&& pred, State&& state, Func&& f) const;
};

inline constexpr const while_t While{};

template <typename Pred, typename State, typename Func>
constexpr decltype(auto) while_t::operator()(Pred&& pred, State&& state, Func&& f) const
{
  using Cond = std::invoke_result_t<Pred, State>;
  if constexpr (integral::is_bool_c_v<Cond>) {
    if constexpr (Cond()) {
      return While(std::forward<Pred>(pred), std::forward<Func>(f)(std::forward<State>(state)), std::forward<Func>(f));
    }
    else {
      return std::forward<State>(state);
    }
  }
  else if constexpr (std::is_convertible_v<Cond, bool>) {
    while (std::forward<Pred>(pred)(std::forward<State>(state))) {
      state = std::forward<Func>(f)(std::forward<State>(state));
    }
    return std::forward<State>(state);
  }
  else {
    throw "Bad type for condition : only std::integral_constant::value_type == bool or integral convertible to bool "
          "allowed!";
  }
}

} // namespace blackmagic::functional
