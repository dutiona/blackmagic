#pragma once

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts, size_t... I>
constexpr auto transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  return std::make_tuple(f(std::get<I>(tpl))...);
}

struct transform_t {
  template <typename Func, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
};

} // namespace details

inline constexpr details::transform_t transform{};

}} // namespace metaprog::tuple::algorithm
