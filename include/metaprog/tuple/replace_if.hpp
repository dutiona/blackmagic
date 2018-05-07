#pragma once

#include "transform.hpp"

#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename T, typename... Ts, size_t... I>
constexpr auto replace_if_impl(const std::tuple<Ts...>& tpl, Func&& f, T&& value, std::index_sequence<I...>)
{
  return transform(tpl, [f, v = value](auto&& e) { return f(e) ? v : e; });
}

} // namespace details

struct replace_if_t {
  template <typename Func, typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, Func&& f, T&& value) const
  {
    return details::replace_if_impl(tpl, std::forward<Func>(f), std::forward<T>(value),
                                    std::index_sequence_for<Ts...>{});
  }
};

inline constexpr replace_if_t replace_if{};

}} // namespace metaprog::tuple::algorithm
