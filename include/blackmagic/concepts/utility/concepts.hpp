#pragma once

#include "../engine.hpp"
#include "traits.hpp"

#include <string_view>

namespace blackmagic::concepts { inline namespace utility {

using namespace std::literals;

inline namespace member_access {
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

} // namespace member_access


inline namespace arithmetic {
// pre_incrementable
inline constexpr auto PreIncrementable = is_true<traits::is_pre_incrementable>("PreIncrementable"sv);

// post_incrementable
inline constexpr auto PostIncrementable = is_true<traits::is_post_incrementable>("PostIncrementable"sv);

// pre_decrementable
inline constexpr auto PreDecrementable = is_true<traits::is_pre_decrementable>("PreDecrementable"sv);

// post_decrementable
inline constexpr auto PostDecrementable = is_true<traits::is_post_decrementable>("PostDecrementable"sv);

// positive
inline constexpr auto Positive = is_true<traits::is_positive>("Positive"sv);

// negative
inline constexpr auto Negative = is_true<traits::is_negative>("Negative"sv);

// not
inline constexpr auto BitNot = is_true<traits::is_bit_not>("Not"sv);

// plus
inline constexpr auto Plus = is_true<traits::is_plus>("Plus"sv);

// less
inline constexpr auto Minus = is_true<traits::is_minus>("Minus"sv);

// mult
inline constexpr auto Mult = is_true<traits::is_mult>("Mult"sv);

// div
inline constexpr auto Div = is_true<traits::is_div>("Div"sv);

// mod
inline constexpr auto Mod = is_true<traits::is_mod>("Mod"sv);

// and
inline constexpr auto BitAnd = is_true<traits::is_bit_and>("BitAnd"sv);

// or
inline constexpr auto BitOr = is_true<traits::is_bit_or>("BitOr"sv);

// xor
inline constexpr auto BitXor = is_true<traits::is_bit_xor>("BitXor"sv);

// lshift
inline constexpr auto BitLshift = is_true<traits::is_bit_lshift>("BitLshift"sv);

// rshift
inline constexpr auto BitRshift = is_true<traits::is_bit_rshift>("BitRshift"sv);


inline namespace assignement {
// assignable
inline constexpr auto Assignable = is_true<traits::is_assignable>("Assignable"sv);

// plus_assignable
inline constexpr auto PlusAssignable = is_true<traits::is_plus_assignable>("PlusAssignable"sv);

// less_assignable
inline constexpr auto MinusAssignable = is_true<traits::is_minus_assignable>("LessAssignable"sv);

// mult_assignable
inline constexpr auto MultAssignable = is_true<traits::is_mult_assignable>("MultAssignable"sv);

// div_assignable
inline constexpr auto DivAssignable = is_true<traits::is_div_assignable>("DivAssignable"sv);

// mod_assignable
inline constexpr auto ModAssignable = is_true<traits::is_mod_assignable>("ModAssignable"sv);

// and_assignable
inline constexpr auto BitAndAssignable = is_true<traits::is_bit_and_assignable>("AndAssignable"sv);

// or_assignable
inline constexpr auto BitOrAssignable = is_true<traits::is_bit_or_assignable>("OrAssignable"sv);

// xor_assignable
inline constexpr auto BitXorAssignable = is_true<traits::is_bit_xor_assignable>("XorAssignable"sv);

// lshift_assignable
inline constexpr auto BitLshiftAssignable = is_true<traits::is_bit_lshift_assignable>("LshiftAssignable"sv);

// rshift_assignable
inline constexpr auto BitRshiftAssignable = is_true<traits::is_bit_rshift_assignable>("RshiftAssignable"sv);

} // namespace assignement

} // namespace arithmetic


inline namespace comparison {
// equality
inline constexpr auto Equality = is_true<traits::is_equality>("Equality"sv);

// inequality
inline constexpr auto Inequality = is_true<traits::is_inequality>("Inequality"sv);

// less
inline constexpr auto Less = is_true<traits::is_less>("Less"sv);

// less_equal
inline constexpr auto LessEqual = is_true<traits::is_less_equal>("LessEqual"sv);

// greater
inline constexpr auto Greater = is_true<traits::is_greater>("Greater"sv);

// greater_equal
inline constexpr auto GreaterEqual = is_true<traits::is_greater_equal>("GreaterEqual"sv);

} // namespace comparison


inline namespace logical {
// logical_not
inline constexpr auto LogicalNot = is_true<traits::is_logical_not>("LogicalNot"sv);

// logical_and
inline constexpr auto LogicalAnd = is_true<traits::is_logical_and>("LogicalAnd"sv);

// logical_or
inline constexpr auto LogicalOr = is_true<traits::is_logical_or>("LogicalOr"sv);

} // namespace logical


inline namespace other {
// comma
inline constexpr auto Comma = is_true<traits::is_comma>("Comma"sv);

// ternary
inline constexpr auto Ternary = is_true<traits::is_ternary>("Ternary"sv);

// invocable
inline constexpr auto Invocable = is_true<traits::is_invocable>("Invocable"sv);

// invocable r
inline constexpr auto InvocableR = is_true<traits::is_invocable_r>("InvocableR"sv);

} // namespace other

}} // namespace blackmagic::concepts::utility
