#pragma once

#include "../engine.hpp"

#include "../engine.hpp"
#include "traits.hpp"

#include <string_view>

namespace metaprog::concepts { inline namespace utility {

using namespace std::literals;
namespace traits = metaprog::traits;

// member access

// indirection
inline constexpr auto Indirection = is_true<traits::is_indirection>("Indirection"sv);

// address_of
inline constexpr auto AddressOf = is_true<traits::is_address_of>("AddressOf"sv);

// subscript
inline constexpr auto Subscript = is_true<traits::is_subscript>("Subscript"sv);

// pointer_to_member_of_object
inline constexpr auto PointerToMemberOfObject =
  is_true<traits::is_pointer_to_member_of_object>("PointerToMemberOfObject"sv);

// pointer_to_member_of_pointer
inline constexpr auto PointerToMemberOfPointer =
  is_true<traits::is_pointer_to_member_of_pointer>("PointerToMemberOfPointer"sv);


// assignement

// assignable
inline constexpr auto Assignable = is_true<traits::is_assignable>("Assignable"sv);

// plus_assignable
inline constexpr auto PlusAssignable = is_true<traits::is_plus_assignable>("PlusAssignable"sv);

// less_assignable
inline constexpr auto LessAssignable = is_true<traits::is_less_assignable>("LessAssignable"sv);

// mult_assignable
inline constexpr auto MultAssignable = is_true<traits::is_mult_assignable>("MultAssignable"sv);

// div_assignable
inline constexpr auto DivAssignable = is_true<traits::is_div_assignable>("DivAssignable"sv);

// mod_assignable
inline constexpr auto ModAssignable = is_true<traits::is_mod_assignable>("ModAssignable"sv);

// and_assignable
inline constexpr auto AndAssignable = is_true<traits::is_and_assignable>("AndAssignable"sv);

// or_assignable
inline constexpr auto OrAssignable = is_true<traits::is_or_assignable>("OrAssignable"sv);

// xor_assignable
inline constexpr auto XorAssignable = is_true<traits::is_xor_assignable>("XorAssignable"sv);

// lshift_assignable
inline constexpr auto LshiftAssignable = is_true<traits::is_lshift_assignable>("LshiftAssignable"sv);

// rshift_assignable
inline constexpr auto RshiftAssignable = is_true<traits::is_rshift_assignable>("RshiftAssignable"sv);


// arithmetic

// positive
inline constexpr auto Positive = is_true<traits::is_positive>("Positive"sv);

// negative
inline constexpr auto Negative = is_true<traits::is_negative>("Negative"sv);

// not
inline constexpr auto Not = is_true<traits::is_not>("Not"sv);

// plus
inline constexpr auto Plus = is_true<traits::is_plus>("Plus"sv);

// less
inline constexpr auto Less = is_true<traits::is_less>("Less"sv);

// mult
inline constexpr auto Mult = is_true<traits::is_mult>("Mult"sv);

// div
inline constexpr auto Div = is_true<traits::is_div>("Div"sv);

// mod
inline constexpr auto Mod = is_true<traits::is_mod>("Mod"sv);

// and
inline constexpr auto And = is_true<traits::is_and>("And"sv);

// or
inline constexpr auto Or = is_true<traits::is_or>("Or"sv);

// xor
inline constexpr auto Xor = is_true<traits::is_xor>("Xor"sv);

// lshift
inline constexpr auto Lshift = is_true<traits::is_lshift>("Lshift"sv);

// rshift
inline constexpr auto Rshift = is_true<traits::is_rshift>("Rshift"sv);


// increment / decrement

// pre_incrementable
inline constexpr auto PreIncrementable = is_true<traits::is_pre_incrementable>("PreIncrementable"sv);

// post_incrementable
inline constexpr auto PostIncrementable = is_true<traits::is_post_incrementable>("PostIncrementable"sv);

// pre_decrementable
inline constexpr auto PreDecrementable = is_true<traits::is_pre_decrementable>("PreDecrementable"sv);

// post_decrementable
inline constexpr auto PostDecrementable = is_true<traits::is_post_decrementable>("PostDecrementable"sv);


// comparison

// equality
inline constexpr auto Equality = is_true<traits::is_equality>("Equality"sv);

// inequality
inline constexpr auto Inequality = is_true<traits::is_inequality>("Inequality"sv);

// less_than
inline constexpr auto LessThan = is_true<traits::is_less_than>("LessThan"sv);

// less_equal_than
inline constexpr auto LessEqualThan = is_true<traits::is_less_equal_than>("LessEqualThan"sv);

// greater_than
inline constexpr auto GreaterThan = is_true<traits::is_greater_than>("GreaterThan"sv);

// greater_equal_than
inline constexpr auto GreaterEqualThan = is_true<traits::is_greater_equal_than>("GreaterEqualThan"sv);


// logical

// logical_not
inline constexpr auto LogicalNot = is_true<traits::is_logical_not>("LogicalNot"sv);

// logical_and
inline constexpr auto LogicalAnd = is_true<traits::is_logical_and>("LogicalAnd"sv);
// logical_or
inline constexpr auto LogicalOr = is_true<traits::is_logical_or>("LogicalOr"sv);


// other

// comma
inline constexpr auto Comma = is_true<traits::is_comma>("Comma"sv);

// ternary
inline constexpr auto Ternary = is_true<traits::is_ternary>("Ternary"sv);

// invocable
inline constexpr auto Invocable = is_true<traits::is_invocable>("Invocable"sv);

// invocable r
inline constexpr auto InvocableR = is_true<traits::is_invocable_r>("InvocableR"sv);

}} // namespace metaprog::concepts::utility
