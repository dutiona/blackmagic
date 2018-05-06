#pragma once

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename T, typename Func, typename... Ts, size_t... I>
constexpr T accumulate_impl(T&& init, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  ((init = f(std::forward<T>(init), std::get<I>(tpl))), ...);
  return init;
}

} // namespace details

struct accumulate_t {
  template <typename T, typename Func, typename... Ts>
  constexpr auto operator()(T&& init, const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return details::accumulate_impl(std::forward<T>(init), tpl, std::index_sequence_for<Ts...>{},
                                    std::forward<Func>(f));
  }
};

inline constexpr accumulate_t accumulate{};

}} // namespace metaprog::tuple::algorithm
