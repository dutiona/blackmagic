#pragma once

#ifndef METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
#define METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../core.hpp"

namespace cpt { namespace layout { namespace diagnostic {

// trivially copyable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::TriviallyCopyable))
{
  static_assert(cpt::concepts::TriviallyCopyable.check<T>(), "T is not trivially copyable");
}

// trivial
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Trivial))
{
  static_assert(cpt::concepts::Trivial.check<T>(), "T is not trivial");
}

// standard layout
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::StandardLayout))
{
  static_assert(cpt::concepts::StandardLayout.check<T>(), "T is not a standard layout");
}

}}} // namespace cpt::layout::diagnostic

#endif // METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
