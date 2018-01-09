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

#include "../verif.hpp"

#include <string_view>

namespace cpt { namespace concepts { namespace layout {

using namespace std::literals;

// trivially copyable
inline constexpr auto trivially_copyable =
  make_custom_concept_item_from_predicate<details::trivially_copyable_impl>("trivially_copyable"sv);

// trivial
inline constexpr auto trivial = make_custom_concept_item_from_predicate<details::trivial_impl>("trivial"sv);

// standard layout
inline constexpr auto standard_layout =
  make_custom_concept_item_from_predicate<details::standard_layout_impl>("standard_layout"sv);

}}} // namespace cpt::concepts::layout

#endif // METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
