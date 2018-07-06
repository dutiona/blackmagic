#pragma once

#include "partial.hpp"

#include <utility>

namespace blackmagic::functional {

// fwd dcl
struct compose_t {
  template <typename... Funcs>
  constexpr decltype(auto) operator()(Funcs&&... fs) const;
};

inline constexpr const compose_t compose{};

namespace details {

template <typename F, typename G>
class compose_caller {
public:
  constexpr compose_caller(F&& f, G&& g)
    : f_(std::forward<F>(f))
    , g_(std::forward<G>(g))
  {
  }

  template <typename Arg0, typename... Args>
  constexpr decltype(auto) operator()(Arg0&& arg0, Args&&... args) const
  {
    return f_(g_(std::forward<Arg0>(arg0)), std::forward<Args>(args)...);
  }

private:
  F f_;
  G g_;
};

template <typename F, typename G>
constexpr decltype(auto) compose_impl(F&& f, G&& g)
{
  return compose_caller<F, G>{std::forward<F>(f), std::forward<G>(g)};
}

template <typename F, typename G, typename... Hs>
constexpr decltype(auto) compose_impl(F&& f, G&& g, Hs&&... hs)
{
  return compose(std::forward<F>(f), compose(std::forward<G>(g), std::forward<Hs>(hs)...));
}

} // namespace details

template <typename... Funcs>
constexpr decltype(auto) compose_t::operator()(Funcs&&... fs) const
{
  static_assert(sizeof...(Funcs) > 1, "Cannot compose less than two invocable!");

  return details::compose_impl(std::forward<Funcs>(fs)...);
}

} // namespace blackmagic::functional
