#pragma once

#ifndef METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
#define METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../verif.hpp"

namespace cpt { namespace layout { namespace diagnostic {

// trivially copyable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::trivially_copyable))
{
  static_assert(cpt::check<T>(cpt::concepts::trivially_copyable), "T is not trivially copyable");
}

// trivial
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::trivial))
{
  static_assert(cpt::check<T>(cpt::concepts::trivial), "T is not trivial");
}

// standard layout
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::standard_layout))
{
  static_assert(cpt::check<T>(cpt::concepts::standard_layout), "T is not a standard layout");
}

}}} // namespace cpt::layout::diagnostic

#endif // METAPROG_CPT_LAYOUT_DIAGNOSTIC_HPP_
