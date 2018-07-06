#pragma once

#include "../../tuple/algorithm/unpack.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::functional::lazy {

template <typename F, typename... Args>
class lazy_expr {
public:
  constexpr lazy_expr(F&& f, Args&&... args)
    : f_(std::forward<F>(f))
    , args_(std::forward<Args>(args)...)
  {
  }

private:
  constexpr decltype(auto) operator()() const
  {
    return tuple::unpack(args_, f_);
  }

  F                   f_;
  std::tuple<Args...> args_;

  friend struct eval_t;
};

struct lazy_t {
  template <typename Func, typename... Args>
  constexpr decltype(auto) operator()(Func&& f, Args&&... args) const
  {
    return lazy_expr<Func, Args...>(std::forward<Func>(f), std::forward<Args>(args)...);
  }
};

inline constexpr const lazy_t make_lazy{};

} // namespace blackmagic::functional::lazy
