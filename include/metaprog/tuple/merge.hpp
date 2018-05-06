#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_front.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

// fwd dcl
struct merge_t {
  template <typename C, typename T, typename... Ts>
  constexpr auto operator()(C&& comp, T&& tpl, Ts&&... tpls) const;
};

inline constexpr merge_t merge{};

namespace details {

template <typename C, typename T, typename U>
constexpr auto merge_two(C&& comp, T&& lhs, U&& rhs)
{
  if constexpr (std::tuple_size_v<T> == 0 && std::tuple_size_v<U> == 0) {
    return std::tuple<>();
  }
  else if constexpr (std::tuple_size_v<T> == 0) {
    return rhs;
  }
  else if constexpr (std::tuple_size_v<U> == 0) {
    return lhs;
  }
  else {
    if (std::forward<C>(comp)(front(lhs), front(rhs))) {
      return push_front(merge_two(std::forward<C>(comp), pop_front(lhs), rhs), front(lhs));
    }
    else {
      return push_front(merge_two(std::forward<C>(comp), lhs, pop_front(rhs)), front(rhs));
    }
  }
}

template <typename C, typename T, typename U, typename... Ts>
constexpr auto merge_impl(C&& comp, T&& lhs, U&& rhs, Ts&&... tpls)
{
  return merge(std::forward<C>(comp), merge_two(std::forward<C>(comp), std::forward<T>(lhs), std::forward<U>(rhs)),
               std::forward<Ts>(tpls)...);
}

template <typename C, typename T, typename... Ts>
constexpr auto merge_impl(C&& comp, T&& tpl, Ts&&... tpls)
{
  if constexpr (sizeof...(Ts) == 0) {
    return std::forward<T>(tpl);
  }
  else {
    return merge_impl(std::forward<C>(comp), std::forward<T>(tpl), std::forward<Ts>(tpls)...);
  }
}

} // namespace details

template <typename C, typename T, typename... Ts>
constexpr auto merge_t::operator()(C&& comp, T&& tpl, Ts&&... tpls) const
{
  return details::merge_impl(std::forward<C>(comp), std::forward<T>(tpl), std::forward<Ts>(tpls)...);
}

}} // namespace metaprog::tuple::algorithm
