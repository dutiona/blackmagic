#pragma once

#ifndef METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
#define METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../core.hpp"

namespace cpt { namespace basic { namespace diagnostic {

// default constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::DefaultConstructible))
{
  static_assert(cpt::concepts::DefaultConstructible.check<T>(), "T is not default constructible");
}

// move constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::MoveConstructible))
{
  static_assert(cpt::concepts::MoveConstructible.check<T>(), "T is not move constructible");
}

// copy constructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::CopyConstructible))
{
  static_assert(cpt::concepts::CopyConstructible.check<T>(), "T is not copy constructible");
}

// move assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::MoveAssignable))
{
  static_assert(cpt::concepts::MoveAssignable.check<T>(), "T is not move assignable");
}

// copy assignable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::CopyAssignable))
{
  static_assert(cpt::concepts::CopyAssignable.check<T>(), "T is not copy assignable");
}

// destructible
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Destructible))
{
  static_assert(cpt::concepts::Destructible.check<T>(), "T is not destructible");
}

}}} // namespace cpt::basic::diagnostic

#endif // METAPROG_CPT_BASIC_DIAGNOSTIC_HPP_
