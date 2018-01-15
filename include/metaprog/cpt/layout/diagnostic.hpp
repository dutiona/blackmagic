#pragma once

#ifndef METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
#define METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_

#include "concepts.hpp"

namespace cpt::layout::diagnostic {

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

} // namespace cpt::layout::diagnostic

#endif // METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
