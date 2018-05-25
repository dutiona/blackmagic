#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct not_equal_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) to(U&&) const;
};

inline constexpr not_equal_functor_t not_equal{};

namespace details {

template <typename T>
struct not_equal_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return not_equal_t<T, U>{};
  }
};

template <typename U>
struct not_equal_functor_impl_to {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return not_equal_t<T, U>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) not_equal_functor_t::operator()(T&&, U&&) const
{
  return not_equal_t<T, U>{};
}

template <typename T>
constexpr decltype(auto) not_equal_functor_t::operator()(T&&) const
{
  return details::not_equal_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) not_equal_functor_t::to(U&&) const
{
  return details::not_equal_functor_impl_to<U>{};
}

}}} // namespace blackmagic::integral::functors::arithmetic
