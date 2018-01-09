#pragma once

#ifndef METAPROG_CPT_UTILIY_CONCEPTS_HPP_
#define METAPROG_CPT_UTILIY_CONCEPTS_HPP_

#include "../verif.hpp"

#include "details/concepts_impl.hpp"

#include <string_view>

namespace cpt { namespace concepts { namespace utility {

using namespace std::literals;

// member access

// indirection
inline constexpr auto indirection = make_concept_item_from_predicate<details::indirection_impl>("indirection"sv);

// address_of
inline constexpr auto address_of = make_concept_item_from_predicate<details::address_of_impl>("address_of"sv);

// subscript
inline constexpr auto subscript = make_concept_item_from_predicate<details::subscript_impl>("subscript"sv);

// pointer_to_member_of_object
inline constexpr auto pointer_to_member_of_object =
  make_concept_item_from_predicate<details::pointer_to_member_of_object_impl>("pointer_to_member_of_object"sv);

// pointer_to_member_of_pointer
inline constexpr auto pointer_to_member_of_pointer =
  make_concept_item_from_predicate<details::pointer_to_member_of_pointer_impl>("pointer_to_member_of_pointer"sv);


// assignement

// assignable
inline constexpr auto assignable = make_concept_item_from_predicate<details::assignable_impl>("assignable"sv);

// plus_assignable
inline constexpr auto plus_assignable =
  make_concept_item_from_predicate<details::plus_assignable_impl>("plus_assignable"sv);

// less_assignable
inline constexpr auto less_assignable =
  make_concept_item_from_predicate<details::less_assignable_impl>("less_assignable"sv);

// mult_assignable
inline constexpr auto mult_assignable =
  make_concept_item_from_predicate<details::mult_assignable_impl>("mult_assignable"sv);

// div_assignable
inline constexpr auto div_assignable =
  make_concept_item_from_predicate<details::div_assignable_impl>("div_assignable"sv);

// mod_assignable
inline constexpr auto mod_assignable =
  make_concept_item_from_predicate<details::mod_assignable_impl>("mod_assignable"sv);

// and_assignable
inline constexpr auto and_assignable =
  make_concept_item_from_predicate<details::and_assignable_impl>("and_assignable"sv);

// or_assignable
inline constexpr auto or_assignable = make_concept_item_from_predicate<details::or_assignable_impl>("or_assignable"sv);

// xor_assignable
inline constexpr auto xor_assignable =
  make_concept_item_from_predicate<details::xor_assignable_impl>("xor_assignable"sv);

// lshift_assignable
inline constexpr auto lshift_assignable =
  make_concept_item_from_predicate<details::lshift_assignable_impl>("lshift_assignable"sv);

// rshift_assignable
inline constexpr auto rshift_assignable =
  make_concept_item_from_predicate<details::rshift_assignable_impl>("rshift_assignable"sv);


// arithmetic

// positive
inline constexpr auto positive = make_concept_item_from_predicate<details::positive_impl>("positive"sv);

// negative
inline constexpr auto negative = make_concept_item_from_predicate<details::negative_impl>("negative"sv);

// not
inline constexpr auto Not = make_concept_item_from_predicate<details::not_impl>("not"sv); // "not" is a c++ keyword

// plus
inline constexpr auto plus = make_concept_item_from_predicate<details::plus_impl>("plus"sv);

// less
inline constexpr auto less = make_concept_item_from_predicate<details::less_impl>("less"sv);

// mult
inline constexpr auto mult = make_concept_item_from_predicate<details::mult_impl>("mult"sv);

// div
inline constexpr auto div = make_concept_item_from_predicate<details::div_impl>("div"sv);

// mod
inline constexpr auto mod = make_concept_item_from_predicate<details::mod_impl>("mod"sv);

// and
inline constexpr auto And = make_concept_item_from_predicate<details::and_impl>("and"sv); // "and" is a c++ keyword

// or
inline constexpr auto Or = make_concept_item_from_predicate<details::or_impl>("or"sv); // "or" is a c++ keyword

// xor
inline constexpr auto Xor = make_concept_item_from_predicate<details::xor_impl>("xor"sv); // "xor" is a c++ keyword

// lshift
inline constexpr auto lshift = make_concept_item_from_predicate<details::lshift_impl>("lshift"sv);

// rshift
inline constexpr auto rshift = make_concept_item_from_predicate<details::rshift_impl>("rshift"sv);


// increment / decrement

// pre_incrementable
inline constexpr auto pre_incrementable =
  make_concept_item_from_predicate<details::pre_incrementable_impl>("pre_incrementable"sv);

// post_incrementable
inline constexpr auto post_incrementable =
  make_concept_item_from_predicate<details::post_incrementable_impl>("post_incrementable"sv);

// pre_decrementable
inline constexpr auto pre_decrementable =
  make_concept_item_from_predicate<details::pre_decrementable_impl>("pre_decrementable"sv);

// post_decrementable
inline constexpr auto post_decrementable =
  make_concept_item_from_predicate<details::post_decrementable_impl>("post_decrementable"sv);


// comparison

// equality
inline constexpr auto equality = make_concept_item_from_predicate<details::equality_impl>("equality"sv);

// inequality
inline constexpr auto inequality = make_concept_item_from_predicate<details::inequality_impl>("inequality"sv);

// less_than
inline constexpr auto less_than = make_concept_item_from_predicate<details::less_than_impl>("less_than"sv);

// less_equal_than
inline constexpr auto less_equal_than =
  make_concept_item_from_predicate<details::less_equal_than_impl>("less_equal_than"sv);

// greater_than
inline constexpr auto greater_than = make_concept_item_from_predicate<details::greater_than_impl>("greater_than"sv);

// greater_equal_than
inline constexpr auto greater_equal_than =
  make_concept_item_from_predicate<details::greater_equal_than_impl>("greater_equal_than"sv);


// logical

// logical_not
inline constexpr auto logical_not = make_concept_item_from_predicate<details::logical_not_impl>("logical_not"sv);

// logical_and
inline constexpr auto logical_and = make_concept_item_from_predicate<details::logical_and_impl>("logical_and"sv);

// logical_or
inline constexpr auto logical_or = make_concept_item_from_predicate<details::logical_or_impl>("logical_or"sv);


// other

// comma
inline constexpr auto comma = make_concept_item_from_predicate<details::comma_impl>("comma"sv);

// ternary
inline constexpr auto ternary = make_concept_item_from_predicate<details::ternary_impl>("ternary"sv);

// invocable
inline constexpr auto invocable = make_concept_item_from_predicate<details::invocable_impl>("invocable"sv);

// invocable r
inline constexpr auto invocable_r = make_concept_item_from_predicate<details::invocable_r_impl>("invocable_r"sv);

}}} // namespace cpt::concepts::utility


#endif // METAPROG_CPT_UTILIY_CONCEPTS_HPP_
