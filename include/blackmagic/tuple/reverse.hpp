#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_front.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename... Ts, typename... Us>
constexpr auto reverse_impl(const std::tuple<Ts...>& tpl, const std::tuple<Us...>& ret)
{
  if constexpr (sizeof...(Ts) == 0) {
    return ret;
  }
  else {
    return reverse_impl(pop_front(tpl), push_front(ret, front(tpl)));
  }
}

struct reverse_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    return details::reverse_impl(tpl, std::tuple<>());
  }
};

} // namespace details

inline constexpr details::reverse_t reverse{};

}} // namespace blackmagic::tuple::algorithm
