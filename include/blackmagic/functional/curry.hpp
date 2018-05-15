#pragma once

#include "partial.hpp"

#include "../integral/integral.hpp"

#include <utility>

namespace blackmagic::functional {

namespace integral = blackmagic::integral;

// fwd dcl
struct curry_t {
  template <typename Func, size_t N>
  constexpr decltype(auto) operator()(Func&& f, integral::size_t_<N>) const;
};

inline constexpr const curry_t curry{};

namespace details {

template <typename Func, size_t N>
class curry_impl {
public:
  constexpr curry_impl(Func&& f)
    : f_(std::forward<Func>(f))
  {
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    static_assert(sizeof...(Args) <= N, "Passing more arguments than the invocable needs.");

    if constexpr (sizeof...(Args) == N) {
      return f_(std::forward<Args>(args)...);
    }
    else {
      return curry(partial(f_, std::forward<Args>(args)...), integral::size_t_<(N - sizeof...(Args))>{});
    }
  }

private:
  const Func f_;
};

} // namespace details

template <typename Func, size_t N>
constexpr decltype(auto) curry_t::operator()(Func&& f, integral::size_t_<N>) const
{
  return details::curry_impl<Func, N>(std::forward<Func>(f));
}

} // namespace blackmagic::functional
