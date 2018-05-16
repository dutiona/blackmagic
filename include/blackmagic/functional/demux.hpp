#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::functional {

namespace details {

template <typename F, typename... Funcs>
class demux_impl_caller {
public:
  constexpr demux_impl_caller(const F& f, Funcs&&... fs)
    : f_(f)
    , funcs_(std::forward<Funcs>(fs)...)
  {
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    return unpack_apply_(std::index_sequence_for<Funcs...>{}, std::forward<Args>(args)...);
  }

private:
  template <typename... Args, size_t... I>
  constexpr decltype(auto) unpack_apply_(std::index_sequence<I...>, Args&&... args) const
  {
    return f_(std::get<I>(funcs_)(std::forward<Args>(args)...)...);
  }

private:
  const F                    f_;
  const std::tuple<Funcs...> funcs_;
};

template <typename F>
class demux_impl {
public:
  constexpr demux_impl(F&& f)
    : f_(std::forward<F>(f))
  {
  }

  template <typename... Funcs>
  constexpr decltype(auto) operator()(Funcs&&... funcs)
  {
    return demux_impl_caller<F, Funcs...>{f_, std::forward<Funcs>(funcs)...};
  }

private:
  const F f_;
};

} // namespace details

struct demux_t {
  template <typename F>
  constexpr decltype(auto) operator()(F&& f) const
  {
    return details::demux_impl<F>{std::forward<F>(f)};
  }
};

inline constexpr const demux_t demux{};

} // namespace blackmagic::functional
