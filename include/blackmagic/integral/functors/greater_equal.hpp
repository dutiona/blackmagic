#pragma once

#include "../utility.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace comparison {

struct greater_equal_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) than(U&&) const;
};

inline constexpr greater_equal_functor_t greater_equal{};

namespace details {

template <typename T>
struct greater_equal_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return greater_equal_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

template <typename U>
struct greater_equal_functor_impl_than {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return greater_equal_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) greater_equal_functor_t::operator()(T&&, U&&) const
{
  return greater_equal_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
}

template <typename T>
constexpr decltype(auto) greater_equal_functor_t::operator()(T&&) const
{
  return details::greater_equal_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) greater_equal_functor_t::than(U&&) const
{
  return details::greater_equal_functor_impl_than<U>{};
}

}}} // namespace blackmagic::integral::functors::comparison
