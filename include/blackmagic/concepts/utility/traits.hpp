#pragma once

#include "details/traits_impl.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::traits { inline namespace utility {

namespace common = blackmagic::common;
using common::_t;
using common::_v;

inline namespace member_access {
// is_indirection : *a
template <typename T>
using is_indirection = details::is_indirection_impl<T>;
template <typename T>
using is_indirection_t = _t<is_indirection<T>>;
template <typename T>
constexpr bool is_indirection_v = _v<is_indirection<T>>;
// is_nothrow_indirection
template <typename T>
using is_nothrow_indirection = details::is_nothrow_indirection_impl<T>;
template <typename T>
using is_nothrow_indirection_t = _t<is_nothrow_indirection<T>>;
template <typename T>
constexpr bool is_nothrow_indirection_v = _v<is_nothrow_indirection<T>>;

// is_address_of : &a
template <typename T>
using is_address_of = details::is_address_of_impl<T>;
template <typename T>
using is_address_of_t = _t<is_address_of<T>>;
template <typename T>
constexpr bool is_address_of_v = _v<is_address_of<T>>;
// is_nothrow_address_of
template <typename T>
using is_nothrow_address_of = details::is_nothrow_address_of_impl<T>;
template <typename T>
using is_nothrow_address_of_t = _t<is_nothrow_address_of<T>>;
template <typename T>
constexpr bool is_nothrow_address_of_v = _v<is_nothrow_address_of<T>>;

// is_subscript : a[b]
template <typename T, typename I>
using is_subscript = details::is_subscript_impl<T, I>;
template <typename T, typename I>
using is_subscript_t = _t<is_subscript<T, I>>;
template <typename T, typename I>
constexpr bool is_subscript_v = _v<is_subscript<T, I>>;
// is_nothrow_subscript
template <typename T, typename I>
using is_nothrow_subscript = details::is_nothrow_subscript_impl<T, I>;
template <typename T, typename I>
using is_nothrow_subscript_t = _t<is_nothrow_subscript<T, I>>;
template <typename T, typename I>
constexpr bool is_nothrow_subscript_v = _v<is_nothrow_subscript<T, I>>;

// is_pointer_to_member_of_object : a.*b
template <typename T, typename I>
using is_pointer_to_member_of_object = details::is_pointer_to_member_of_object_impl<T, I>;
template <typename T, typename I>
using is_pointer_to_member_of_object_t = _t<is_pointer_to_member_of_object<T, I>>;
template <typename T, typename I>
constexpr bool is_pointer_to_member_of_object_v = _v<is_pointer_to_member_of_object<T, I>>;
// is_nothrow_pointer_to_member_of_object
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_object = details::is_nothrow_pointer_to_member_of_object_impl<T, I>;
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_object_t = _t<is_nothrow_pointer_to_member_of_object<T, I>>;
template <typename T, typename I>
constexpr bool is_nothrow_pointer_to_member_of_object_v = _v<is_nothrow_pointer_to_member_of_object<T, I>>;

// is_pointer_to_member_of_pointer : a->*b
template <typename T, typename I>
using is_pointer_to_member_of_pointer = details::is_pointer_to_member_of_pointer_impl<T, I>;
template <typename T, typename I>
using is_pointer_to_member_of_pointer_t = _t<is_pointer_to_member_of_pointer<T, I>>;
template <typename T, typename I>
constexpr bool is_pointer_to_member_of_pointer_v = _v<is_pointer_to_member_of_pointer<T, I>>;
// is_nothrow_pointer_to_member_of_pointer
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_pointer = details::is_nothrow_pointer_to_member_of_pointer_impl<T, I>;
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_pointer_t = _t<is_nothrow_pointer_to_member_of_pointer<T, I>>;
template <typename T, typename I>
constexpr bool is_nothrow_pointer_to_member_of_pointer_v = _v<is_nothrow_pointer_to_member_of_pointer<T, I>>;

} // namespace member_access

inline namespace arithmetic {
// is_pre_incrementable : ++a
template <typename T>
using is_pre_incrementable = details::is_pre_incrementable_impl<T>;
template <typename T>
using is_pre_incrementable_t = _t<is_pre_incrementable<T>>;
template <typename T>
constexpr bool is_pre_incrementable_v = _v<is_pre_incrementable<T>>;
// is_nothrow_pre_incrementable
template <typename T>
using is_nothrow_pre_incrementable = details::is_nothrow_pre_incrementable_impl<T>;
template <typename T>
using is_nothrow_pre_incrementable_t = _t<is_nothrow_pre_incrementable<T>>;
template <typename T>
constexpr bool is_nothrow_pre_incrementable_v = _v<is_nothrow_pre_incrementable<T>>;

// is_post_incrementable : a++
template <typename T>
using is_post_incrementable = details::is_post_incrementable_impl<T>;
template <typename T>
using is_post_incrementable_t = _t<is_post_incrementable<T>>;
template <typename T>
constexpr bool is_post_incrementable_v = _v<is_post_incrementable<T>>;
// is_nothrow_post_incrementable
template <typename T>
using is_nothrow_post_incrementable = details::is_nothrow_post_incrementable_impl<T>;
template <typename T>
using is_nothrow_post_incrementable_t = _t<is_nothrow_post_incrementable<T>>;
template <typename T>
constexpr bool is_nothrow_post_incrementable_v = _v<is_nothrow_post_incrementable<T>>;

// is_pre_decrementable : --a
template <typename T>
using is_pre_decrementable = details::is_pre_decrementable_impl<T>;
template <typename T>
using is_pre_decrementable_t = _t<is_pre_decrementable<T>>;
template <typename T>
constexpr bool is_pre_decrementable_v = _v<is_pre_decrementable<T>>;
// is_nothrow_pre_decrementable
template <typename T>
using is_nothrow_pre_decrementable = details::is_nothrow_pre_decrementable_impl<T>;
template <typename T>
using is_nothrow_pre_decrementable_t = _t<is_nothrow_pre_decrementable<T>>;
template <typename T>
constexpr bool is_nothrow_pre_decrementable_v = _v<is_nothrow_pre_decrementable<T>>;

// is_post_decrementable : a--
template <typename T>
using is_post_decrementable = details::is_post_decrementable_impl<T>;
template <typename T>
using is_post_decrementable_t = _t<is_post_decrementable<T>>;
template <typename T>
constexpr bool is_post_decrementable_v = _v<is_post_decrementable<T>>;
// is_nothrow_post_decrementable
template <typename T>
using is_nothrow_post_decrementable = details::is_nothrow_post_decrementable_impl<T>;
template <typename T>
using is_nothrow_post_decrementable_t = _t<is_nothrow_post_decrementable<T>>;
template <typename T>
constexpr bool is_nothrow_post_decrementable_v = _v<is_nothrow_post_decrementable<T>>;

// is_positive : +a
template <typename T>
using is_positive = details::is_positive_impl<T>;
template <typename T>
using is_positive_t = _t<is_positive<T>>;
template <typename T>
constexpr bool is_positive_v = _v<is_positive<T>>;
// is_nothrow_positive
template <typename T>
using is_nothrow_positive = details::is_nothrow_positive_impl<T>;
template <typename T>
using is_nothrow_positive_t = _t<is_nothrow_positive<T>>;
template <typename T>
constexpr bool is_nothrow_positive_v = _v<is_nothrow_positive<T>>;

// is_negative : -a
template <typename T>
using is_negative = details::is_negative_impl<T>;
template <typename T>
using is_negative_t = _t<is_negative<T>>;
template <typename T>
constexpr bool is_negative_v = _v<is_negative<T>>;
// is_nothrow_negative
template <typename T>
using is_nothrow_negative = details::is_nothrow_negative_impl<T>;
template <typename T>
using is_nothrow_negative_t = _t<is_nothrow_negative<T>>;
template <typename T>
constexpr bool is_nothrow_negative_v = _v<is_nothrow_negative<T>>;

// is_bit_not : ~a
template <typename T>
using is_bit_not = details::is_bit_not_impl<T>;
template <typename T>
using is_bit_not_t = _t<is_bit_not<T>>;
template <typename T>
constexpr bool is_bit_not_v = _v<is_bit_not<T>>;
// is_nothrow_bit_not
template <typename T>
using is_nothrow_bit_not = details::is_nothrow_bit_not_impl<T>;
template <typename T>
using is_nothrow_bit_not_t = _t<is_nothrow_bit_not<T>>;
template <typename T>
constexpr bool is_nothrow_bit_not_v = _v<is_nothrow_bit_not<T>>;

// is_plus : a + b
template <typename T, typename U = T>
using is_plus = details::is_plus_impl<T, U>;
template <typename T, typename U = T>
using is_plus_t = _t<is_plus<T, U>>;
template <typename T, typename U = T>
constexpr bool is_plus_v = _v<is_plus<T, U>>;
// is_nothrow_plus
template <typename T, typename U = T>
using is_nothrow_plus = details::is_nothrow_plus_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_plus_t = _t<is_nothrow_plus<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_plus_v = _v<is_nothrow_plus<T, U>>;

// is_minus : a - b
template <typename T, typename U = T>
using is_minus = details::is_minus_impl<T, U>;
template <typename T, typename U = T>
using is_minus_t = _t<is_minus<T, U>>;
template <typename T, typename U = T>
constexpr bool is_minus_v = _v<is_minus<T, U>>;
// is_nothrow_minus
template <typename T, typename U = T>
using is_nothrow_minus = details::is_nothrow_minus_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_minus_t = _t<is_nothrow_minus<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_minus_v = _v<is_nothrow_minus<T, U>>;

// is_mult : a * b
template <typename T, typename U = T>
using is_mult = details::is_mult_impl<T, U>;
template <typename T, typename U = T>
using is_mult_t = _t<is_mult<T, U>>;
template <typename T, typename U = T>
constexpr bool is_mult_v = _v<is_mult<T, U>>;
// is_nothrow_mult
template <typename T, typename U = T>
using is_nothrow_mult = details::is_nothrow_mult_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mult_t = _t<is_nothrow_mult<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_mult_v = _v<is_nothrow_mult<T, U>>;

// is_div : a / b
template <typename T, typename U = T>
using is_div = details::is_div_impl<T, U>;
template <typename T, typename U = T>
using is_div_t = _t<is_div<T, U>>;
template <typename T, typename U = T>
constexpr bool is_div_v = _v<is_div<T, U>>;
// is_nothrow_div
template <typename T, typename U = T>
using is_nothrow_div = details::is_nothrow_div_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_div_t = _t<is_nothrow_div<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_div_v = _v<is_nothrow_div<T, U>>;

// is_mod : a % b
template <typename T, typename U = T>
using is_mod = details::is_mod_impl<T, U>;
template <typename T, typename U = T>
using is_mod_t = _t<is_mod<T, U>>;
template <typename T, typename U = T>
constexpr bool is_mod_v = _v<is_mod<T, U>>;
// is_nothrow_mod
template <typename T, typename U = T>
using is_nothrow_mod = details::is_nothrow_mod_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mod_t = _t<is_nothrow_mod<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_mod_v = _v<is_nothrow_mod<T, U>>;

// is_bit_and : a & b
template <typename T, typename U = T>
using is_bit_and = details::is_bit_and_impl<T, U>;
template <typename T, typename U = T>
using is_bit_and_t = _t<is_bit_and<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_and_v = _v<is_bit_and<T, U>>;
// is_nothrow_bit_and
template <typename T, typename U = T>
using is_nothrow_bit_and = details::is_nothrow_bit_and_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_and_t = _t<is_nothrow_bit_and<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_and_v = _v<is_nothrow_bit_and<T, U>>;

// is_bit_or : a | b
template <typename T, typename U = T>
using is_bit_or = details::is_bit_or_impl<T, U>;
template <typename T, typename U = T>
using is_bit_or_t = _t<is_bit_or<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_or_v = _v<is_bit_or<T, U>>;
// is_nothrow_bit_or
template <typename T, typename U = T>
using is_nothrow_bit_or = details::is_nothrow_bit_or_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_or_t = _t<is_nothrow_bit_or<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_or_v = _v<is_nothrow_bit_or<T, U>>;

// is_bit_xor : a ^ b
template <typename T, typename U = T>
using is_bit_xor = details::is_bit_xor_impl<T, U>;
template <typename T, typename U = T>
using is_bit_xor_t = _t<is_bit_xor<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_xor_v = _v<is_bit_xor<T, U>>;
// is_nothrow_bit_xor
template <typename T, typename U = T>
using is_nothrow_bit_xor = details::is_nothrow_bit_xor_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_xor_t = _t<is_nothrow_bit_xor<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_xor_v = _v<is_nothrow_bit_xor<T, U>>;

// is_bit_lshift : a << b
template <typename T, typename U = T>
using is_bit_lshift = details::is_bit_lshift_impl<T, U>;
template <typename T, typename U = T>
using is_bit_lshift_t = _t<is_bit_lshift<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_lshift_v = _v<is_bit_lshift<T, U>>;
// is_nothrow_bit_lshift
template <typename T, typename U = T>
using is_nothrow_bit_lshift = details::is_nothrow_bit_lshift_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_lshift_t = _t<is_nothrow_bit_lshift<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_lshift_v = _v<is_nothrow_bit_lshift<T, U>>;

// is_bit_rshift : a >> b
template <typename T, typename U = T>
using is_bit_rshift = details::is_bit_rshift_impl<T, U>;
template <typename T, typename U = T>
using is_bit_rshift_t = _t<is_bit_rshift<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_rshift_v = _v<is_bit_rshift<T, U>>;
// is_nothrow_bit_rshift
template <typename T, typename U = T>
using is_nothrow_bit_rshift = details::is_nothrow_bit_rshift_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_rshift_t = _t<is_nothrow_bit_rshift<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_rshift_v = _v<is_nothrow_bit_rshift<T, U>>;


inline namespace assignement {
// is_assignable : a = b
template <typename T, typename U = T>
using is_assignable = details::is_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_assignable_t = _t<is_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_assignable_v = _v<is_assignable<T, U>>;
// is_nothrow_assignable
template <typename T, typename U = T>
using is_nothrow_assignable = details::is_nothrow_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_assignable_t = _t<is_nothrow_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_assignable_v = _v<is_nothrow_assignable<T, U>>;

// is_plus_assignable : a += b
template <typename T, typename U = T>
using is_plus_assignable = details::is_plus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_plus_assignable_t = _t<is_plus_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_plus_assignable_v = _v<is_plus_assignable<T, U>>;
// is_nothrow_plus_assignable
template <typename T, typename U = T>
using is_nothrow_plus_assignable = details::is_nothrow_plus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_plus_assignable_t = _t<is_nothrow_plus_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_plus_assignable_v = _v<is_nothrow_plus_assignable<T, U>>;

// is_minus_assignable : a -= b
template <typename T, typename U = T>
using is_minus_assignable = details::is_minus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_minus_assignable_t = _t<is_minus_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_minus_assignable_v = _v<is_minus_assignable<T, U>>;
// is_nothrow_minus_assignable
template <typename T, typename U = T>
using is_nothrow_minus_assignable = details::is_nothrow_minus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_minus_assignabl_t = _t<is_nothrow_minus_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_minus_assignable_v = _v<is_nothrow_minus_assignable<T, U>>;

// is_mult_assignable : a *= b
template <typename T, typename U = T>
using is_mult_assignable = details::is_mult_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_mult_assignable_t = _t<is_mult_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_mult_assignable_v = _v<is_mult_assignable<T, U>>;
// is_nothrow_mult_assignable
template <typename T, typename U = T>
using is_nothrow_mult_assignable = details::is_nothrow_mult_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mult_assignable_t = _t<is_nothrow_mult_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_mult_assignable_v = _v<is_nothrow_mult_assignable<T, U>>;

// is_div_assignable : a /= b
template <typename T, typename U = T>
using is_div_assignable = details::is_div_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_div_assignable_t = _t<is_div_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_div_assignable_v = _v<is_div_assignable<T, U>>;
// is_nothrow_div_assignable
template <typename T, typename U = T>
using is_nothrow_div_assignable = details::is_nothrow_div_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_div_assignable_t = _t<is_nothrow_div_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_div_assignable_v = _v<is_nothrow_div_assignable<T, U>>;

// is_mod_assignable : a %= b
template <typename T, typename U = T>
using is_mod_assignable = details::is_mod_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_mod_assignable_t = _t<is_mod_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_mod_assignable_v = _v<is_mod_assignable<T, U>>;
// is_nothrow_mod_assignable
template <typename T, typename U = T>
using is_nothrow_mod_assignable = details::is_nothrow_mod_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mod_assignable_t = _t<is_nothrow_mod_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_mod_assignable_v = _v<is_nothrow_mod_assignable<T, U>>;

// is_bit_and_assignable : a &= b
template <typename T, typename U = T>
using is_bit_and_assignable = details::is_bit_and_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_bit_and_assignable_t = _t<is_bit_and_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_and_assignable_v = _v<is_bit_and_assignable<T, U>>;
// is_nothrow_bit_and_assignable
template <typename T, typename U = T>
using is_nothrow_bit_and_assignable = details::is_nothrow_bit_and_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_and_assignable_t = _t<is_nothrow_bit_and_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_and_assignable_v = _v<is_nothrow_bit_and_assignable<T, U>>;

// is_bit_or_assignable : a |= b
template <typename T, typename U = T>
using is_bit_or_assignable = details::is_bit_or_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_bit_or_assignable_t = _t<is_bit_or_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_or_assignable_v = _v<is_bit_or_assignable<T, U>>;
// is_nothrow_bit_or_assignable
template <typename T, typename U = T>
using is_nothrow_bit_or_assignable = details::is_nothrow_bit_or_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_or_assignable_t = _t<is_nothrow_bit_or_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_or_assignable_v = _v<is_nothrow_bit_or_assignable<T, U>>;

// is_bit_xor_assignable : a ^= b
template <typename T, typename U = T>
using is_bit_xor_assignable = details::is_bit_xor_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_bit_xor_assignable_t = _t<is_bit_xor_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_xor_assignable_v = _v<is_bit_xor_assignable<T, U>>;
// is_nothrow_bit_xor_assignable
template <typename T, typename U = T>
using is_nothrow_bit_xor_assignable = details::is_nothrow_bit_xor_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_xor_assignable_t = _t<is_nothrow_bit_xor_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_xor_assignable_v = _v<is_nothrow_bit_xor_assignable<T, U>>;

// is_bit_lshift_assignable : a <<= b
template <typename T, typename U = T>
using is_bit_lshift_assignable = details::is_bit_lshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_bit_lshift_assignable_t = _t<is_bit_lshift_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_lshift_assignable_v = _v<is_bit_lshift_assignable<T, U>>;
// is_nothrow_bit_lshift_assignable
template <typename T, typename U = T>
using is_nothrow_bit_lshift_assignable = details::is_nothrow_bit_lshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_lshift_assignable_t = _t<is_nothrow_bit_lshift_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_lshift_assignable_v = _v<is_nothrow_bit_lshift_assignable<T, U>>;

// is_bit_rshift_assignable : a >>= b
template <typename T, typename U = T>
using is_bit_rshift_assignable = details::is_bit_rshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_bit_rshift_assignable_t = _t<is_bit_rshift_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_bit_rshift_assignable_v = _v<is_bit_rshift_assignable<T, U>>;
// is_nothrow_bit_rshift_assignable
template <typename T, typename U = T>
using is_nothrow_bit_rshift_assignable = details::is_nothrow_bit_rshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_bit_rshift_assignable_t = _t<is_nothrow_bit_rshift_assignable<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_bit_rshift_assignable_v = _v<is_nothrow_bit_rshift_assignable<T, U>>;

} // namespace assignement

} // namespace arithmetic


inline namespace comparison {
// is_equality : a == b
template <typename T, typename U = T>
using is_equality = details::is_equality_impl<T, U>;
template <typename T, typename U = T>
using is_equality_t = _t<is_equality<T, U>>;
template <typename T, typename U = T>
constexpr bool is_equality_v = _v<is_equality<T, U>>;
// is_nothrow_equality
template <typename T, typename U = T>
using is_nothrow_equality = details::is_nothrow_equality_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_equality_t = _t<is_nothrow_equality<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_equality_v = _v<is_nothrow_equality<T, U>>;

// is_inequality : a != b
template <typename T, typename U = T>
using is_inequality = details::is_inequality_impl<T, U>;
template <typename T, typename U = T>
using is_inequality_t = _t<is_inequality<T, U>>;
template <typename T, typename U = T>
constexpr bool is_inequality_v = _v<is_inequality<T, U>>;
// is_nothrow_inequality
template <typename T, typename U = T>
using is_nothrow_inequality = details::is_nothrow_inequality_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_inequality_t = _t<is_nothrow_inequality<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_inequality_v = _v<is_nothrow_inequality<T, U>>;

// is_less : a < b
template <typename T, typename U = T>
using is_less = details::is_less_impl<T, U>;
template <typename T, typename U = T>
using is_less_t = _t<is_less<T, U>>;
template <typename T, typename U = T>
constexpr bool is_less_v = _v<is_less<T, U>>;
// is_nothrow_less
template <typename T, typename U = T>
using is_nothrow_less = details::is_nothrow_less_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_t = _t<is_nothrow_less<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_v = _v<is_nothrow_less<T, U>>;

// is_less_equal : a <= b
template <typename T, typename U = T>
using is_less_equal = details::is_less_equal_impl<T, U>;
template <typename T, typename U = T>
using is_less_equal_t = _t<is_less_equal<T, U>>;
template <typename T, typename U = T>
constexpr bool is_less_equal_v = _v<is_less_equal<T, U>>;
// is_nothrow_less_equal
template <typename T, typename U = T>
using is_nothrow_less_equal = details::is_nothrow_less_equal_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_equal_t = _t<is_nothrow_less_equal<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_equal_v = _v<is_nothrow_less_equal<T, U>>;

// is_greater : a > b
template <typename T, typename U = T>
using is_greater = details::is_greater_impl<T, U>;
template <typename T, typename U = T>
using is_greater_t = _t<is_greater<T, U>>;
template <typename T, typename U = T>
constexpr bool is_greater_v = _v<is_greater<T, U>>;
// is_nothrow_greater
template <typename T, typename U = T>
using is_nothrow_greater = details::is_nothrow_greater_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_greater_t = _t<is_nothrow_greater<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_greater_v = _v<is_nothrow_greater<T, U>>;

// is_greater_equal : a >= b
template <typename T, typename U = T>
using is_greater_equal = details::is_greater_equal_impl<T, U>;
template <typename T, typename U = T>
using is_greater_equal_t = _t<is_greater_equal<T, U>>;
template <typename T, typename U = T>
constexpr bool is_greater_equal_v = _v<is_greater_equal<T, U>>;
// is_nothrow_greater_equal
template <typename T, typename U = T>
using is_nothrow_greater_equal = details::is_nothrow_greater_equal_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_greater_equal_t = _t<is_nothrow_greater_equal<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_greater_equal_v = _v<is_nothrow_greater_equal<T, U>>;

} // namespace comparison


inline namespace logical {
// is_logical_not
template <typename T>
using is_logical_not = details::is_logical_not_impl<T>;
template <typename T>
using is_logical_not_t = _t<is_logical_not<T>>;
template <typename T>
constexpr bool is_logical_not_v = _v<is_logical_not<T>>;
// is_nothrow_logical_not
template <typename T>
using is_nothrow_logical_not = details::is_nothrow_logical_not_impl<T>;
template <typename T>
using is_nothrow_logical_not_t = _t<is_nothrow_logical_not<T>>;
template <typename T>
constexpr bool is_nothrow_logical_not_v = _v<is_nothrow_logical_not<T>>;

// is_logical_and
template <typename T, typename U = T>
using is_logical_and = details::is_logical_and_impl<T, U>;
template <typename T, typename U = T>
using is_logical_and_t = _t<is_logical_and<T, U>>;
template <typename T, typename U = T>
constexpr bool is_logical_and_v = _v<is_logical_and<T, U>>;
// is_nothrow_logical_and
template <typename T, typename U = T>
using is_nothrow_logical_and = details::is_nothrow_logical_and_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_logical_and_t = _t<is_nothrow_logical_and<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_logical_and_v = _v<is_nothrow_logical_and<T, U>>;

// is_logical_or
template <typename T, typename U = T>
using is_logical_or = details::is_logical_or_impl<T, U>;
template <typename T, typename U = T>
using is_logical_or_t = _t<is_logical_or<T, U>>;
template <typename T, typename U = T>
constexpr bool is_logical_or_v = _v<is_logical_or<T, U>>;
// is_nothrow_logical_or
template <typename T, typename U = T>
using is_nothrow_logical_or = details::is_nothrow_logical_or_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_logical_or_t = _t<is_nothrow_logical_or<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_logical_or_v = _v<is_nothrow_logical_or<T, U>>;

} // namespace logical


inline namespace other {
// is_comma
template <typename T, typename U = T>
using is_comma = details::is_comma_impl<T, U>;
template <typename T, typename U = T>
using is_comma_t = _t<is_comma<T, U>>;
template <typename T, typename U = T>
constexpr bool is_comma_v = _v<is_comma<T, U>>;
// is_nothrow_comma
template <typename T, typename U = T>
using is_nothrow_comma = details::is_nothrow_comma_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_comma_t = _t<is_nothrow_comma<T, U>>;
template <typename T, typename U = T>
constexpr bool is_nothrow_comma_v = _v<is_nothrow_comma<T, U>>;

// is_ternary
template <typename B, typename T, typename U = T>
using is_ternary = details::is_ternary_impl<B, T, U>;
template <typename B, typename T, typename U = T>
using is_ternary_t = _t<is_ternary<T, U>>;
template <typename B, typename T, typename U = T>
constexpr bool is_ternary_v = _v<is_ternary<T, U>>;
// is_nothrow_ternary
template <typename B, typename T, typename U = T>
using is_nothrow_ternary = details::is_nothrow_ternary_impl<B, T, U>;
template <typename B, typename T, typename U = T>
using is_nothrow_ternary_t = _t<is_nothrow_ternary<T, U>>;
template <typename B, typename T, typename U = T>
constexpr bool is_nothrow_ternary_v = _v<is_nothrow_ternary<T, U>>;

// is_invocable : f(args...)
template <typename F, typename... Args>
using is_invocable = details::is_invocable_impl<details::_holder<F, Args...>>;
template <typename F, typename... Args>
using is_invocable_t = _t<is_invocable<F, Args...>>;
template <typename F, typename... Args>
constexpr bool is_invocable_v = _v<is_invocable<F, Args...>>;
// is_nothrow_invocable
template <typename F, typename... Args>
using is_nothrow_invocable = details::is_nothrow_invocable_impl<details::_holder<F, Args...>>;
template <typename F, typename... Args>
using is_nothrow_invocable_t = _t<is_nothrow_invocable<F, Args...>>;
template <typename F, typename... Args>
constexpr bool is_nothrow_invocable_v = _v<is_nothrow_invocable<F, Args...>>;

// is_invocable_r : r f(args...)
template <typename R, typename F, typename... Args>
using is_invocable_r = details::is_invocable_r_impl<details::_holder_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
using is_invocable_r_t = _t<is_invocable_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
constexpr bool is_invocable_r_v = _v<is_invocable_r<R, F, Args...>>;
// is_nothrow_invocable_r : r f(args...)
template <typename R, typename F, typename... Args>
using is_nothrow_invocable_r = details::is_nothrow_invocable_r_impl<details::_holder_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
using is_nothrow_invocable_r_t = _t<is_nothrow_invocable_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
constexpr bool is_nothrow_invocable_r_v = _v<is_nothrow_invocable_r<R, F, Args...>>;

} // namespace other

}} // namespace blackmagic::traits::utility
