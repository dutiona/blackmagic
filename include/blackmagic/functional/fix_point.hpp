#pragma once

#include <utility>

namespace blackmagic::functional {

struct fix_point_t {
  template <typename Func>
  constexpr decltype(auto) operator()(Func&& f) const;
};

inline constexpr const fix_point_t fix_point{};

namespace details {

template <typename F>
class fix_point_impl {
public:
  constexpr fix_point_impl(F&& f)
    : f_(std::forward<F>(f))
  {
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    return f_(fix_point(f_), std::forward<Args>(args)...);
  }

private:
  F f_;
};

} // namespace details

template <typename Func>
constexpr decltype(auto) fix_point_t::operator()(Func&& f) const
{
  return details::fix_point_impl<Func>{std::forward<Func>(f)};
}

} // namespace blackmagic::functional
