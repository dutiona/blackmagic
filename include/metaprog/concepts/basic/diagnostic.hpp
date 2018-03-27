#pragma once

#include "concepts.hpp"

namespace metaprog::diagnostic { inline namespace basic {

namespace concepts = metaprog::concepts;

// default constructible
template <typename T>
constexpr void diagnostic(decltype(concepts::DefaultConstructible))
{
  static_assert(concepts::DefaultConstructible.check<T>(), "T is not default constructible");
}

// move constructible
template <typename T>
constexpr void diagnostic(decltype(concepts::MoveConstructible))
{
  static_assert(concepts::MoveConstructible.check<T>(), "T is not move constructible");
}

// copy constructible
template <typename T>
constexpr void diagnostic(decltype(concepts::CopyConstructible))
{
  static_assert(concepts::CopyConstructible.check<T>(), "T is not copy constructible");
}

// move assignable
template <typename T>
constexpr void diagnostic(decltype(concepts::MoveAssignable))
{
  static_assert(concepts::MoveAssignable.check<T>(), "T is not move assignable");
}

// copy assignable
template <typename T>
constexpr void diagnostic(decltype(concepts::CopyAssignable))
{
  static_assert(concepts::CopyAssignable.check<T>(), "T is not copy assignable");
}

// destructible
template <typename T>
constexpr void diagnostic(decltype(concepts::Destructible))
{
  static_assert(concepts::Destructible.check<T>(), "T is not destructible");
}

}} // namespace concepts::basic::diagnostic
