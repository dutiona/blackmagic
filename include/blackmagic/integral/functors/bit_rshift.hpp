#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace arithmetic {

struct bit_rshift_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) by(U&&) const;
};

inline constexpr bit_rshift_functor_t bit_rshift{};

namespace details {

template <typename T>
struct bit_rshift_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return bit_rshift_t<T, U>{};
  }
};

template <typename U>
struct bit_rshift_functor_impl_by {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return bit_rshift_t<T, U>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) bit_rshift_functor_t::operator()(T&&, U&&) const
{
  return bit_rshift_t<T, U>{};
}

template <typename T>
constexpr decltype(auto) bit_rshift_functor_t::operator()(T&&) const
{
  return details::bit_rshift_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) bit_rshift_functor_t::by(U&&) const
{
  return details::bit_rshift_functor_impl_by<U>{};
}

}}} // namespace blackmagic::integral::functors::arithmetic
