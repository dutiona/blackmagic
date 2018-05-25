#pragma once

#include "../integral/types.hpp"

#include <utility>

namespace blackmagic::functional {

struct iterate_t {
  template <typename Func, size_t N>
  constexpr decltype(auto) operator()(Func&& f, integral::size_t_t<N>) const;
};

inline constexpr const iterate_t iterate{};

namespace details {

template <typename F, size_t N>
class iterate_impl {
public:
  constexpr iterate_impl(F&& f)
    : f_(std::forward<F>(f))
  {
  }

  template <typename T>
  constexpr decltype(auto) operator()(T&& v) const
  {
    if constexpr (N == 0) {
      return std::forward<T>(v);
    }
    else {
      return f_(iterate(f_, integral::size_t_t<(N - 1)>{})(std::forward<T>(v)));
    }
  }

private:
  const F f_;
};

} // namespace details

template <typename Func, size_t N>
constexpr decltype(auto) iterate_t::operator()(Func&& f, integral::size_t_t<N>) const
{
  return details::iterate_impl<Func, N>{std::forward<Func>(f)};
}

} // namespace blackmagic::functional
