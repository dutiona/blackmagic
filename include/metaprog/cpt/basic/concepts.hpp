#pragma once

#ifndef METAPROG_CPT_BASIC_CONCEPTS_HPP_
#define METAPROG_CPT_BASIC_CONCEPTS_HPP_

/**
 *
 * default constructible : specifies that an object of the type can be default
 * constructed
 *
 * move constructible : specifies that an object of the type can be constructed
 * from rvalue
 *
 * copy constructible : specifies that an object of the type can be constructed
 * from lvalue
 *
 * move assignable : specifies that an object of the type can be assigned from
 * rvalue
 *
 * copy assignable : specifies that an object of the type can be assigned from
 * lvalue
 *
 * destructible : specifies that an object of the type can be destroyed
 *
 */

#include "details/concepts_impl.hpp"

#include "../verif.hpp"

#include <string_view>

namespace cpt { namespace concepts { namespace basic {

using namespace std::literals;

// default constructible
inline constexpr auto default_constructible =
  make_concept_item_from_predicate<details::default_constructible_impl>("default_constructible"sv);

// move constructible
inline constexpr auto move_constructible =
  make_concept_item_from_predicate<details::move_constructible_impl>("move_constructible"sv);

// copy constructible
inline constexpr auto copy_constructible =
  make_concept_item_from_predicate<details::copy_constructible_impl>("copy_constructible"sv);

// move assignable
inline constexpr auto move_assignable =
  make_concept_item_from_predicate<details::move_assignable_impl>("move_assignable"sv);

// copy assignable
inline constexpr auto copy_assignable =
  make_concept_item_from_predicate<details::copy_assignable_impl>("copy_assignable"sv);

// destructible
inline constexpr auto destructible = make_concept_item_from_predicate<details::destructible_impl>("destructible"sv);

}}} // namespace cpt::concepts::basic

#endif // METAPROG_CPT_BASIC_CONCEPTS_HPP_
