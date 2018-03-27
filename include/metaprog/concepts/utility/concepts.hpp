#pragma once

#include "../core.hpp"

#include "details/concepts_impl.hpp"

#include <string_view>

namespace metaprog::concepts { inline namespace utility {

using namespace std::literals;

// member access

// indirection
inline constexpr auto Indirection = make_concept_item_from_predicate<details::indirection_impl>("Indirection"sv);

// address_of
inline constexpr auto AddressOf = make_concept_item_from_predicate<details::address_of_impl>("AddressOf"sv);

// subscript
inline constexpr auto Subscript = make_concept_item_from_predicate<details::subscript_impl>("Subscript"sv);

// pointer_to_member_of_object
inline constexpr auto PointerToMemberOfObject =
  make_concept_item_from_predicate<details::pointer_to_member_of_object_impl>("PointerToMemberOfObject"sv);

// pointer_to_member_of_pointer
inline constexpr auto PointerToMemberOfPointer =
  make_concept_item_from_predicate<details::pointer_to_member_of_pointer_impl>("PointerToMemberOfPointer"sv);


// assignement

// assignable
inline constexpr auto Assignable = make_concept_item_from_predicate<details::assignable_impl>("Assignable"sv);

// plus_assignable
inline constexpr auto PlusAssignable =
  make_concept_item_from_predicate<details::plus_assignable_impl>("PlusAssignable"sv);

// less_assignable
inline constexpr auto LessAssignable =
  make_concept_item_from_predicate<details::less_assignable_impl>("LessAssignable"sv);

// mult_assignable
inline constexpr auto MultAssignable =
  make_concept_item_from_predicate<details::mult_assignable_impl>("MultAssignable"sv);

// div_assignable
inline constexpr auto DivAssignable = make_concept_item_from_predicate<details::div_assignable_impl>("DivAssignable"sv);

// mod_assignable
inline constexpr auto ModAssignable = make_concept_item_from_predicate<details::mod_assignable_impl>("ModAssignable"sv);

// and_assignable
inline constexpr auto AndAssignable = make_concept_item_from_predicate<details::and_assignable_impl>("AndAssignable"sv);

// or_assignable
inline constexpr auto OrAssignable = make_concept_item_from_predicate<details::or_assignable_impl>("OrAssignable"sv);

// xor_assignable
inline constexpr auto XorAssignable = make_concept_item_from_predicate<details::xor_assignable_impl>("XorAssignable"sv);

// lshift_assignable
inline constexpr auto LshiftAssignable =
  make_concept_item_from_predicate<details::lshift_assignable_impl>("LshiftAssignable"sv);

// rshift_assignable
inline constexpr auto RshiftAssignable =
  make_concept_item_from_predicate<details::rshift_assignable_impl>("RshiftAssignable"sv);


// arithmetic

// positive
inline constexpr auto Positive = make_concept_item_from_predicate<details::positive_impl>("Positive"sv);

// negative
inline constexpr auto Negative = make_concept_item_from_predicate<details::negative_impl>("Negative"sv);

// not
inline constexpr auto Not = make_concept_item_from_predicate<details::not_impl>("Not"sv);

// plus
inline constexpr auto Plus = make_concept_item_from_predicate<details::plus_impl>("Plus"sv);

// less
inline constexpr auto Less = make_concept_item_from_predicate<details::less_impl>("Less"sv);

// mult
inline constexpr auto Mult = make_concept_item_from_predicate<details::mult_impl>("Mult"sv);

// div
inline constexpr auto Div = make_concept_item_from_predicate<details::div_impl>("Div"sv);

// mod
inline constexpr auto Mod = make_concept_item_from_predicate<details::mod_impl>("Mod"sv);

// and
inline constexpr auto And = make_concept_item_from_predicate<details::and_impl>("And"sv);

// or
inline constexpr auto Or = make_concept_item_from_predicate<details::or_impl>("Or"sv);

// xor
inline constexpr auto Xor = make_concept_item_from_predicate<details::xor_impl>("Xor"sv);

// lshift
inline constexpr auto Lshift = make_concept_item_from_predicate<details::lshift_impl>("Lshift"sv);

// rshift
inline constexpr auto Rshift = make_concept_item_from_predicate<details::rshift_impl>("Rshift"sv);


// increment / decrement

// pre_incrementable
inline constexpr auto PreIncrementable =
  make_concept_item_from_predicate<details::pre_incrementable_impl>("PreIncrementable"sv);

// post_incrementable
inline constexpr auto PostIncrementable =
  make_concept_item_from_predicate<details::post_incrementable_impl>("PostIncrementable"sv);

// pre_decrementable
inline constexpr auto PreDecrementable =
  make_concept_item_from_predicate<details::pre_decrementable_impl>("PreDecrementable"sv);

// post_decrementable
inline constexpr auto PostDecrementable =
  make_concept_item_from_predicate<details::post_decrementable_impl>("PostDecrementable"sv);


// comparison

// equality
inline constexpr auto Equality = make_concept_item_from_predicate<details::equality_impl>("Equality"sv);

// inequality
inline constexpr auto Inequality = make_concept_item_from_predicate<details::inequality_impl>("Inequality"sv);

// less_than
inline constexpr auto LessThan = make_concept_item_from_predicate<details::less_than_impl>("LessThan"sv);

// less_equal_than
inline constexpr auto LessEqualThan =
  make_concept_item_from_predicate<details::less_equal_than_impl>("LessEqualThan"sv);

// greater_than
inline constexpr auto GreaterThan = make_concept_item_from_predicate<details::greater_than_impl>("GreaterThan"sv);

// greater_equal_than
inline constexpr auto GreaterEqualThan =
  make_concept_item_from_predicate<details::greater_equal_than_impl>("GreaterEqualThan"sv);


// logical

// logical_not
inline constexpr auto LogicalNot = make_concept_item_from_predicate<details::logical_not_impl>("LogicalNot"sv);

// logical_and
inline constexpr auto LogicalAnd = make_concept_item_from_predicate<details::logical_and_impl>("LogicalAnd"sv);
// logical_or
inline constexpr auto LogicalOr = make_concept_item_from_predicate<details::logical_or_impl>("LogicalOr"sv);


// other

// comma
inline constexpr auto Comma = make_concept_item_from_predicate<details::comma_impl>("Comma"sv);

// ternary
inline constexpr auto Ternary = make_concept_item_from_predicate<details::ternary_impl>("Ternary"sv);

// invocable
inline constexpr auto Invocable = make_concept_item_from_predicate<details::invocable_impl>("Invocable"sv);

// invocable r
inline constexpr auto InvocableR = make_concept_item_from_predicate<details::invocable_r_impl>("InvocableR"sv);

}} // namespace metaprog::concepts::utility
