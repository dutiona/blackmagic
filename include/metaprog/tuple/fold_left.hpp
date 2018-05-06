#pragma once

#include "push_front.hpp"

#include "../type/type.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace type = metaprog::type;

namespace details {

template <typename Func, typename T, size_t I>
constexpr auto fold_left_impl(const std::tuple<T>& tpl, Func&&, std::index_sequence<I>)
{
  return std::get<I>(tpl);
}

template <typename Func, typename T, typename U, typename... Vs, size_t I, size_t J, size_t... K>
constexpr decltype(auto) fold_left_impl(const std::tuple<T, U, Vs...>& tpl, Func&& f, std::index_sequence<I, J, K...>)
{
  return fold_left_impl(push_front(std::make_tuple(std::get<K>(tpl)...), f(std::get<I>(tpl), std::get<J>(tpl))),
                        std::forward<Func>(f),
                        std::make_index_sequence<type::plus<type::size_t_<sizeof...(Vs)>, type::int_<1>>::value>{});
}

} // namespace details

struct fold_left_t {
  template <typename Func, typename... Ts, typename... Args>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args) const
  {
    return details::fold_left_impl(std::tuple_cat(std::make_tuple(std::forward<Args>(args)...), tpl),
                                   std::forward<Func>(f), std::index_sequence_for<Args..., Ts...>{});
  }
};

inline constexpr fold_left_t fold_left{};

}} // namespace metaprog::tuple::algorithm
