#pragma once

#include "../utility.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace comparison {

struct less_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) than(U&&) const;
};

inline constexpr less_functor_t less{};

namespace details {

template <typename T>
struct less_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return less_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

template <typename U>
struct less_functor_impl_than {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return less_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) less_functor_t::operator()(T&&, U&&) const
{
  return less_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
}

template <typename T>
constexpr decltype(auto) less_functor_t::operator()(T&&) const
{
  return details::less_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) less_functor_t::than(U&&) const
{
  return details::less_functor_impl_than<U>{};
}

}}} // namespace blackmagic::integral::functors::comparison
