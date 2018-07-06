#pragma once

#include <utility>

namespace blackmagic::functional {

namespace details {

template <typename F>
class flip_impl {
public:
  constexpr flip_impl(F&& f)
    : f_(std::forward<F>(f))
  {
  }

  template <typename Arg0, typename Arg1, typename... Args>
  constexpr decltype(auto) operator()(Arg0&& arg0, Arg1&& arg1, Args&&... args) const
  {
    return f_(std::forward<Arg1>(arg1), std::forward<Arg0>(arg0), std::forward<Args>(args)...);
  }

private:
  F f_;
};

} // namespace details

struct flip_t {
  template <typename Func, typename Arg0, typename Arg1, typename... Args>
  constexpr decltype(auto) operator()(Func&& f, Arg0&& arg0, Arg1&& arg1, Args&&... args) const
  {
    return details::flip_impl<Func>{std::forward<Func>(f), std::forward<Arg0>(arg0), std::forward<Arg1>(arg1),
                                    std::forward<Args>(args)...};
  }
};

inline constexpr const flip_t flip{};

} // namespace blackmagic::functional
