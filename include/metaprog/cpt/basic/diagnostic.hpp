#pragma once

#ifndef METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
#define METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../core.hpp"

namespace cpt { namespace basic { namespace diagnostic {

// default constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::default_constructible))
{
  static_assert(cpt::concepts::default_constructible.check<T>(), "T is not default constructible");
}

// move constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::move_constructible))
{
  static_assert(cpt::concepts::move_constructible.check<T>(), "T is not move constructible");
}

// copy constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::copy_constructible))
{
  static_assert(cpt::concepts::copy_constructible.check<T>(), "T is not copy constructible");
}

// move assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::move_assignable))
{
  static_assert(cpt::concepts::move_assignable.check<T>(), "T is not move assignable");
}

// copy assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::copy_assignable))
{
  static_assert(cpt::concepts::copy_assignable.check<T>(), "T is not copy assignable");
}

// destructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::destructible))
{
  static_assert(cpt::concepts::destructible.check<T>(), "T is not destructible");
}

}}} // namespace cpt::basic::diagnostic

#endif // METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
