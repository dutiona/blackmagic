#pragma once

#include "concepts.hpp"

namespace metaprog::diagnostic { inline namespace layout {

namespace concepts = metaprog::concepts;

// trivially copyable
template <typename T>
constexpr void diagnostic(decltype(concepts::TriviallyCopyable))
{
  static_assert(concepts::TriviallyCopyable.check<T>(), "T is not trivially copyable");
}

// trivial
template <typename T>
constexpr void diagnostic(decltype(concepts::Trivial))
{
  static_assert(concepts::Trivial.check<T>(), "T is not trivial");
}

// standard layout
template <typename T>
constexpr void diagnostic(decltype(concepts::StandardLayout))
{
  static_assert(concepts::StandardLayout.check<T>(), "T is not a standard layout");
}

}} // namespace metaprog::diagnostic::layout
