#pragma once

#include "../utility.hpp"

namespace blackmagic::integral { inline namespace functors { inline namespace comparison {

struct greater_functor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&&, U&&) const;

  template <typename T>
  constexpr decltype(auto) operator()(T&&) const;

  template <typename U>
  constexpr decltype(auto) than(U&&) const;
};

inline constexpr greater_functor_t greater{};

namespace details {

template <typename T>
struct greater_functor_impl_rhs {
  template <typename U>
  constexpr decltype(auto) operator()(U&&) const
  {
    return greater_t<T, U>{};
  }
};

template <typename U>
struct greater_functor_impl_than {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return greater_t<T, U>{};
  }
};

} // namespace details

template <typename T, typename U>
constexpr decltype(auto) greater_functor_t::operator()(T&&, U&&) const
{
  return greater_t<T, U>{};
}

template <typename T>
constexpr decltype(auto) greater_functor_t::operator()(T&&) const
{
  return details::greater_functor_impl_rhs<T>{};
}

template <typename U>
constexpr decltype(auto) greater_functor_t::than(U&&) const
{
  return details::greater_functor_impl_than<U>{};
}

}}} // namespace blackmagic::integral::functors::comparison
