#pragma once

#include "arg.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::functional {

struct lockstep_t {
  template <typename Func>
  constexpr decltype(auto) operator()(Func&& f) const;
};

inline constexpr const lockstep_t lockstep{};

namespace details {

template <typename F, typename... Funcs>
class lockstep_impl_caller {
public:
  constexpr lockstep_impl_caller(const F& f, Funcs&&... fs)
    : f_(f)
    , funcs_(std::forward_as_tuple(std::forward<Funcs>(fs)...))
  {
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    static_assert(sizeof...(Args) == sizeof...(Funcs), "Number of passed arguments and invocables are different!");

    return unpack_select_(std::index_sequence_for<Funcs...>{}, std::forward_as_tuple(std::forward<Args>(args)...));
  }

private:
  template <size_t... I, typename... Args>
  constexpr decltype(auto) unpack_select_(std::index_sequence<I...>, const std::tuple<Args...>& args_tpl) const
  {
    return f_(std::get<I>(funcs_)(std::get<I>(args_tpl))...);
  }

private:
  const F                    f_;
  const std::tuple<Funcs...> funcs_;
};

template <typename F>
class lockstep_impl {
public:
  constexpr lockstep_impl(F&& f)
    : f_(std::forward<F>(f))
  {
  }

  template <typename... Funcs>
  constexpr decltype(auto) operator()(Funcs&&... fs)
  {
    return details::lockstep_impl_caller<F, Funcs...>{f_, std::forward<Funcs>(fs)...};
  }

private:
  const F f_;
};

} // namespace details

template <typename Func>
constexpr decltype(auto) lockstep_t::operator()(Func&& f) const
{
  return details::lockstep_impl<Func>{std::forward<Func>(f)};
}

} // namespace blackmagic::functional
