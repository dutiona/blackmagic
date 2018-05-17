#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts, size_t... I>
constexpr auto transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  return std::make_tuple(std::forward<Func>(f)(std::get<I>(tpl))...);
}

} // namespace details

struct transform_t {
  template <typename Func, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return details::transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
};

inline constexpr const transform_t transform{};

}} // namespace blackmagic::tuple::algorithm
