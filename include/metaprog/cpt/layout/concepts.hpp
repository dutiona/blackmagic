#pragma once

#ifndef METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
#define METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
/**
 *
 *
 * trivially copyable : class with trivial copy, assignment and destructor
 *
 * trivial : class with trivial constructors, assignment and destructor
 *
 * standard layout : non-virtual class containing only other StandardLayout
 * members, all with the same access control
 *
 */

#include "details/concepts_impl.hpp"

#include "../core.hpp"

#include <string_view>

namespace cpt { namespace concepts { namespace layout {

using namespace std::literals;

// trivially copyable
inline constexpr auto TriviallyCopyable =
  make_concept_item_from_predicate<details::trivially_copyable_impl>("TriviallyCopyable"sv);

// trivial
inline constexpr auto Trivial = make_concept_item_from_predicate<details::trivial_impl>("Trivial"sv);

// standard layout
inline constexpr auto StandardLayout =
  make_concept_item_from_predicate<details::standard_layout_impl>("StandardLayout"sv);

}}} // namespace cpt::concepts::layout

#endif // METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
