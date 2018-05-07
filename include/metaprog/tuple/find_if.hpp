#pragma once

#include "end.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<>, Func&&)
{
  return end(tpl);
}

template <typename Func, typename... Ts, size_t I, size_t... J>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I, J...>, Func&& f)
{
  return !f(std::get<I>(tpl)) ? find_if_impl(tpl, std::index_sequence<J...>{}, std::forward<Func>(f)) : I;
}

} // namespace details

struct find_if_t {
  template <typename Func, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return details::find_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
  }
};

inline constexpr find_if_t find_if{};

}} // namespace metaprog::tuple::algorithm
