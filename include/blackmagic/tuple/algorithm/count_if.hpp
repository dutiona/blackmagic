#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts, size_t... I>
constexpr size_t count_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  size_t ret = 0;
  ((ret += std::forward<Func>(f)(std::get<I>(tpl)) ? 1 : 0), ...);
  return ret;
}

} // namespace details

struct count_if_t {
  template <typename Func, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return details::count_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
};

inline constexpr const count_if_t count_if{};

}} // namespace blackmagic::tuple::algorithm
