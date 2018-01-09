#pragma once

#ifndef METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
#define METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../verif.hpp"

namespace cpt { namespace basic { namespace diagnostic {

// default constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::default_constructible))
{
  static_assert(cpt::check<T>(cpt::concepts::default_constructible), "T is not default constructible");
}

// move constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::move_constructible))
{
  static_assert(cpt::check<T>(cpt::concepts::move_constructible), "T is not move constructible");
}

// copy constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::copy_constructible))
{
  static_assert(cpt::check<T>(cpt::concepts::copy_constructible), "T is not copy constructible");
}

// move assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::move_assignable))
{
  static_assert(cpt::check<T>(cpt::concepts::move_assignable), "T is not move assignable");
}

// copy assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::copy_assignable))
{
  static_assert(cpt::check<T>(cpt::concepts::copy_assignable), "T is not copy assignable");
}

// destructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::destructible))
{
  static_assert(cpt::check<T>(cpt::concepts::destructible), "T is not destructible");
}

}}} // namespace cpt::basic::concept_diagnostic_traits

#endif // METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
