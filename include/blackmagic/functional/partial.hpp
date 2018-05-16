#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::functional {

// fwd dcl
struct partial_t {
  template <typename Func, typename... Args>
  constexpr decltype(auto) operator()(Func&& f, Args&&... args) const;
};

inline constexpr const partial_t partial{};

namespace details {

template <typename Indexes, typename Func, typename... Args>
class partial_impl;

template <size_t... I, typename Func, typename... Args>
class partial_impl<std::index_sequence<I...>, Func, Args...> {
public:
  constexpr partial_impl(Func&& f, Args&&... args)
    : f_(std::forward<Func>(f))
    , args_(std::forward<Args>(args)...)
  {
  }

  template <typename... Y>
  constexpr decltype(auto) operator()(Y&&... ys) const
  {
    return f_(std::get<I>(args_)..., std::forward<Y>(ys)...);
  }

private:
  const Func                f_;
  const std::tuple<Args...> args_;
};

} // namespace details

template <typename Func, typename... Args>
constexpr decltype(auto) partial_t::operator()(Func&& f, Args&&... args) const
{
  return details::partial_impl<std::index_sequence_for<Args...>, Func, Args...>{std::forward<Func>(f),
                                                                                std::forward<Args>(args)...};
}

} // namespace blackmagic::functional
