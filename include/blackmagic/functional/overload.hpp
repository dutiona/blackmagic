#pragma once

#include <utility>

namespace blackmagic::functional {

namespace details {

template <typename... Funcs>
struct overload_impl : Funcs... {
  using Funcs::operator()...;
};

template <typename... Funcs>
overload_impl(Funcs&&...)->overload_impl<Funcs...>;

} // namespace details

struct overload_t {
  template <typename... Funcs>
  constexpr decltype(auto) operator()(Funcs&&... funcs) const
  {
    return details::overload_impl{std::forward<Funcs>(funcs)...};
  }
};

inline constexpr const overload_t overload{};

} // namespace blackmagic::functional
