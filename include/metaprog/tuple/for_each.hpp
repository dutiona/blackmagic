#pragma once

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts, size_t... I>
constexpr void for_each_impl(std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  (f(std::get<I>(tpl)), ...);
}

template <typename Func, typename... Ts, size_t... I>
constexpr void for_each_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  (f(std::get<I>(tpl)), ...);
}

struct for_each_t {
  template <typename Func, typename... Ts>
  constexpr void operator()(std::tuple<Ts...>& tpl, Func&& f) const
  {
    for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
  template <typename Func, typename... Ts>
  constexpr void operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
};

} // namespace details

inline constexpr details::for_each_t for_each{};

}} // namespace metaprog::tuple::algorithm
