#pragma once

#include "../utility.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace logical {

struct logical_or_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) with(U&&) const;
};

inline constexpr logical_or_functor_t logical_or{};

namespace details {

template <typename T>
struct logical_or_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return logical_or_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

template <typename U>
struct logical_or_functor_impl_with {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return logical_or_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) logical_or_functor_t::operator()(T&&, U&&) const
{
  return logical_or_t<common::remove_cvref_t<T>, common::remove_cvref_t<U>>{};
}

template <typename T>
constexpr decltype(auto) logical_or_functor_t::operator()(T&&) const
{
  return details::logical_or_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) logical_or_functor_t::with(U&&) const
{
  return details::logical_or_functor_impl_with<U>{};
}

}}} // namespace blackmagic::integral::functors::logical
