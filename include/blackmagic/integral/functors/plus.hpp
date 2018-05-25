#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct plus_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) by(U&&) const;
};

inline constexpr plus_functor_t plus{};

namespace details {

template <typename T>
struct plus_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return plus_t<T, U>{};
  }
};

template <typename U>
struct plus_functor_impl_by {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return plus_t<T, U>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) plus_functor_t::operator()(T&&, U&&) const
{
  return plus_t<T, U>{};
}

template <typename T>
constexpr decltype(auto) plus_functor_t::operator()(T&&) const
{
  return details::plus_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) plus_functor_t::by(U&&) const
{
  return details::plus_functor_impl_by<U>{};
}

}}} // namespace blackmagic::integral::functors::arithmetic
