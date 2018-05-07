#pragma once

#include "details/traits_impl.hpp"

#include "../../type/type.hpp"

namespace metaprog::traits { inline namespace utility {

// member access

// is_indirection : *a
template <typename T>
using is_indirection = details::is_indirection_impl<T>;
template <typename T>
using is_indirection_t = typename is_indirection<T>::type;
template <typename T>
constexpr bool is_indirection_v = is_indirection<T>::value;
// is_nothrow_indirection
template <typename T>
using is_nothrow_indirection = details::is_nothrow_indirection_impl<T>;
template <typename T>
using is_nothrow_indirection_t = typename is_nothrow_indirection<T>::type;
template <typename T>
constexpr bool is_nothrow_indirection_v = is_nothrow_indirection<T>::value;

// is_address_of : &a
template <typename T>
using is_address_of = details::is_address_of_impl<T>;
template <typename T>
using is_address_of_t = typename is_address_of<T>::type;
template <typename T>
constexpr bool is_address_of_v = is_address_of<T>::value;
// is_nothrow_address_of
template <typename T>
using is_nothrow_address_of = details::is_nothrow_address_of_impl<T>;
template <typename T>
using is_nothrow_address_of_t = typename is_nothrow_address_of<T>::type;
template <typename T>
constexpr bool is_nothrow_address_of_v = is_nothrow_address_of<T>::value;

// is_subscript : a[b]
template <typename T, typename I>
using is_subscript = details::is_subscript_impl<T, I>;
template <typename T, typename I>
using is_subscript_t = typename is_subscript<T, I>::type;
template <typename T, typename I>
constexpr bool is_subscript_v = is_subscript<T, I>::value;
// is_nothrow_subscript
template <typename T, typename I>
using is_nothrow_subscript = details::is_nothrow_subscript_impl<T, I>;
template <typename T, typename I>
using is_nothrow_subscript_t = typename is_nothrow_subscript<T, I>::type;
template <typename T, typename I>
constexpr bool is_nothrow_subscript_v = is_nothrow_subscript<T, I>::value;

// is_pointer_to_member_of_object : a.*b
template <typename T, typename I>
using is_pointer_to_member_of_object = details::is_pointer_to_member_of_object_impl<T, I>;
template <typename T, typename I>
using is_pointer_to_member_of_object_t = typename is_pointer_to_member_of_object<T, I>::type;
template <typename T, typename I>
constexpr bool is_pointer_to_member_of_object_v = is_pointer_to_member_of_object<T, I>::value;
// is_nothrow_pointer_to_member_of_object
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_object = details::is_nothrow_pointer_to_member_of_object_impl<T, I>;
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_object_t = typename is_nothrow_pointer_to_member_of_object<T, I>::type;
template <typename T, typename I>
constexpr bool is_nothrow_pointer_to_member_of_object_v = is_nothrow_pointer_to_member_of_object<T, I>::value;

// is_pointer_to_member_of_pointer : a->*b
template <typename T, typename I>
using is_pointer_to_member_of_pointer = details::is_pointer_to_member_of_pointer_impl<T, I>;
template <typename T, typename I>
using is_pointer_to_member_of_pointer_t = typename is_pointer_to_member_of_pointer<T, I>::type;
template <typename T, typename I>
constexpr bool is_pointer_to_member_of_pointer_v = is_pointer_to_member_of_pointer<T, I>::value;
// is_nothrow_pointer_to_member_of_pointer
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_pointer = details::is_nothrow_pointer_to_member_of_pointer_impl<T, I>;
template <typename T, typename I>
using is_nothrow_pointer_to_member_of_pointer_t = typename is_nothrow_pointer_to_member_of_pointer<T, I>::type;
template <typename T, typename I>
constexpr bool is_nothrow_pointer_to_member_of_pointer_v = is_nothrow_pointer_to_member_of_pointer<T, I>::value;


// assignement

// is_assignable : a = b
template <typename T, typename U = T>
using is_assignable = details::is_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_assignable_t = typename is_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_assignable_v = is_assignable<T, U>::value;
// is_nothrow_assignable
template <typename T, typename U = T>
using is_nothrow_assignable = details::is_nothrow_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_assignable_t = typename is_nothrow_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;

// is_plus_assignable : a += b
template <typename T, typename U = T>
using is_plus_assignable = details::is_plus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_plus_assignable_t = typename is_plus_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_plus_assignable_v = is_plus_assignable<T, U>::value;
// is_nothrow_plus_assignable
template <typename T, typename U = T>
using is_nothrow_plus_assignable = details::is_nothrow_plus_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_plus_assignable_t = typename is_nothrow_plus_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_plus_assignable_v = is_nothrow_plus_assignable<T, U>::value;

// is_less_assignable : a -= b
template <typename T, typename U = T>
using is_less_assignable = details::is_less_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_less_assignable_t = typename is_less_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_less_assignable_v = is_less_assignable<T, U>::value;
// is_nothrow_less_assignable
template <typename T, typename U = T>
using is_nothrow_less_assignable = details::is_nothrow_less_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_assignable_t = typename is_nothrow_less_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_assignable_v = is_nothrow_less_assignable<T, U>::value;

// is_mult_assignable : a *= b
template <typename T, typename U = T>
using is_mult_assignable = details::is_mult_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_mult_assignable_t = typename is_mult_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_mult_assignable_v = is_mult_assignable<T, U>::value;
// is_nothrow_mult_assignable
template <typename T, typename U = T>
using is_nothrow_mult_assignable = details::is_nothrow_mult_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mult_assignable_t = typename is_nothrow_mult_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_mult_assignable_v = is_nothrow_mult_assignable<T, U>::value;

// is_div_assignable : a /= b
template <typename T, typename U = T>
using is_div_assignable = details::is_div_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_div_assignable_t = typename is_div_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_div_assignable_v = is_div_assignable<T, U>::value;
// is_nothrow_div_assignable
template <typename T, typename U = T>
using is_nothrow_div_assignable = details::is_nothrow_div_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_div_assignable_t = typename is_nothrow_div_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_div_assignable_v = is_nothrow_div_assignable<T, U>::value;

// is_mod_assignable : a %= b
template <typename T, typename U = T>
using is_mod_assignable = details::is_mod_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_mod_assignable_t = typename is_mod_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_mod_assignable_v = is_mod_assignable<T, U>::value;
// is_nothrow_mod_assignable
template <typename T, typename U = T>
using is_nothrow_mod_assignable = details::is_nothrow_mod_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mod_assignable_t = typename is_nothrow_mod_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_mod_assignable_v = is_nothrow_mod_assignable<T, U>::value;

// is_and_assignable : a &= b
template <typename T, typename U = T>
using is_and_assignable = details::is_and_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_and_assignable_t = typename is_and_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_and_assignable_v = is_and_assignable<T, U>::value;
// is_nothrow_and_assignable
template <typename T, typename U = T>
using is_nothrow_and_assignable = details::is_nothrow_and_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_and_assignable_t = typename is_nothrow_and_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_and_assignable_v = is_nothrow_and_assignable<T, U>::value;

// is_or_assignable : a |= b
template <typename T, typename U = T>
using is_or_assignable = details::is_or_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_or_assignable_t = typename is_or_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_or_assignable_v = is_or_assignable<T, U>::value;
// is_nothrow_or_assignable
template <typename T, typename U = T>
using is_nothrow_or_assignable = details::is_nothrow_or_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_or_assignable_t = typename is_nothrow_or_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_or_assignable_v = is_nothrow_or_assignable<T, U>::value;

// is_xor_assignable : a ^= b
template <typename T, typename U = T>
using is_xor_assignable = details::is_xor_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_xor_assignable_t = typename is_xor_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_xor_assignable_v = is_xor_assignable<T, U>::value;
// is_nothrow_xor_assignable
template <typename T, typename U = T>
using is_nothrow_xor_assignable = details::is_nothrow_xor_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_xor_assignable_t = typename is_nothrow_xor_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_xor_assignable_v = is_nothrow_xor_assignable<T, U>::value;

// is_lshift_assignable : a <<= b
template <typename T, typename U = T>
using is_lshift_assignable = details::is_lshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_lshift_assignable_t = typename is_lshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_lshift_assignable_v = is_lshift_assignable<T, U>::value;
// is_nothrow_lshift_assignable
template <typename T, typename U = T>
using is_nothrow_lshift_assignable = details::is_nothrow_lshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_lshift_assignable_t = typename is_nothrow_lshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_lshift_assignable_v = is_nothrow_lshift_assignable<T, U>::value;

// is_rshift_assignable : a >>= b
template <typename T, typename U = T>
using is_rshift_assignable = details::is_rshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_rshift_assignable_t = typename is_rshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_rshift_assignable_v = is_rshift_assignable<T, U>::value;
// is_nothrow_rshift_assignable
template <typename T, typename U = T>
using is_nothrow_rshift_assignable = details::is_nothrow_rshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_rshift_assignable_t = typename is_nothrow_rshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_rshift_assignable_v = is_nothrow_rshift_assignable<T, U>::value;


// arithmetic

// is_positive : +a
template <typename T>
using is_positive = details::is_positive_impl<T>;
template <typename T>
using is_positive_t = typename is_positive<T>::type;
template <typename T>
constexpr bool is_positive_v = is_positive<T>::value;
// is_nothrow_positive
template <typename T>
using is_nothrow_positive = details::is_nothrow_positive_impl<T>;
template <typename T>
using is_nothrow_positive_t = typename is_nothrow_positive<T>::type;
template <typename T>
constexpr bool is_nothrow_positive_v = is_nothrow_positive<T>::value;

// is_negative : -a
template <typename T>
using is_negative = details::is_negative_impl<T>;
template <typename T>
using is_negative_t = typename is_negative<T>::type;
template <typename T>
constexpr bool is_negative_v = is_negative<T>::value;
// is_nothrow_negative
template <typename T>
using is_nothrow_negative = details::is_nothrow_negative_impl<T>;
template <typename T>
using is_nothrow_negative_t = typename is_nothrow_negative<T>::type;
template <typename T>
constexpr bool is_nothrow_negative_v = is_nothrow_negative<T>::value;

// is_not : ~a
template <typename T>
using is_not = details::is_not_impl<T>;
template <typename T>
using is_not_t = typename is_not<T>::type;
template <typename T>
constexpr bool is_not_v = is_not<T>::value;
// is_nothrow_not
template <typename T>
using is_nothrow_not = details::is_nothrow_not_impl<T>;
template <typename T>
using is_nothrow_not_t = typename is_nothrow_not<T>::type;
template <typename T>
constexpr bool is_nothrow_not_v = is_nothrow_not<T>::value;

// is_plus : a + b
template <typename T, typename U = T>
using is_plus = details::is_plus_impl<T, U>;
template <typename T, typename U = T>
using is_plus_t = typename is_plus<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_plus_v = is_plus<T, U>::value;
// is_nothrow_plus
template <typename T, typename U = T>
using is_nothrow_plus = details::is_nothrow_plus_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_plus_t = typename is_nothrow_plus<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_plus_v = is_nothrow_plus<T, U>::value;

// is_less : a - b
template <typename T, typename U = T>
using is_less = details::is_less_impl<T, U>;
template <typename T, typename U = T>
using is_less_t = typename is_less<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_less_v = is_less<T, U>::value;
// is_nothrow_less
template <typename T, typename U = T>
using is_nothrow_less = details::is_nothrow_less_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_t = typename is_nothrow_less<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_v = is_nothrow_less<T, U>::value;

// is_mult : a * b
template <typename T, typename U = T>
using is_mult = details::is_mult_impl<T, U>;
template <typename T, typename U = T>
using is_mult_t = typename is_mult<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_mult_v = is_mult<T, U>::value;
// is_nothrow_mult
template <typename T, typename U = T>
using is_nothrow_mult = details::is_nothrow_mult_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mult_t = typename is_nothrow_mult<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_mult_v = is_nothrow_mult<T, U>::value;

// is_div : a / b
template <typename T, typename U = T>
using is_div = details::is_div_impl<T, U>;
template <typename T, typename U = T>
using is_div_t = typename is_div<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_div_v = is_div<T, U>::value;
// is_nothrow_div
template <typename T, typename U = T>
using is_nothrow_div = details::is_nothrow_div_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_div_t = typename is_nothrow_div<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_div_v = is_nothrow_div<T, U>::value;

// is_mod : a % b
template <typename T, typename U = T>
using is_mod = details::is_mod_impl<T, U>;
template <typename T, typename U = T>
using is_mod_t = typename is_mod<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_mod_v = is_mod<T, U>::value;
// is_nothrow_mod
template <typename T, typename U = T>
using is_nothrow_mod = details::is_nothrow_mod_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_mod_t = typename is_nothrow_mod<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_mod_v = is_nothrow_mod<T, U>::value;

// is_and : a & b
template <typename T, typename U = T>
using is_and = details::is_and_impl<T, U>;
template <typename T, typename U = T>
using is_and_t = typename is_and<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_and_v = is_and<T, U>::value;
// is_nothrow_and
template <typename T, typename U = T>
using is_nothrow_and = details::is_nothrow_and_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_and_t = typename is_nothrow_and<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_and_v = is_nothrow_and<T, U>::value;

// is_or : a | b
template <typename T, typename U = T>
using is_or = details::is_or_impl<T, U>;
template <typename T, typename U = T>
using is_or_t = typename is_or<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_or_v = is_or<T, U>::value;
// is_nothrow_or
template <typename T, typename U = T>
using is_nothrow_or = details::is_nothrow_or_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_or_t = typename is_nothrow_or<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_or_v = is_nothrow_or<T, U>::value;

// is_xor : a ^ b
template <typename T, typename U = T>
using is_xor = details::is_xor_impl<T, U>;
template <typename T, typename U = T>
using is_xor_t = typename is_xor<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_xor_v = is_xor<T, U>::value;
// is_nothrow_xor
template <typename T, typename U = T>
using is_nothrow_xor = details::is_nothrow_xor_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_xor_t = typename is_nothrow_xor<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_xor_v = is_nothrow_xor<T, U>::value;

// is_lshift : a << b
template <typename T, typename U = T>
using is_lshift = details::is_lshift_impl<T, U>;
template <typename T, typename U = T>
using is_lshift_t = typename is_lshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_lshift_v = is_lshift<T, U>::value;
// is_nothrow_lshift
template <typename T, typename U = T>
using is_nothrow_lshift = details::is_nothrow_lshift_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_lshift_t = typename is_nothrow_lshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_lshift_v = is_nothrow_lshift<T, U>::value;

// is_rshift : a >> b
template <typename T, typename U = T>
using is_rshift = details::is_rshift_impl<T, U>;
template <typename T, typename U = T>
using is_rshift_t = typename is_rshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_rshift_v = is_rshift<T, U>::value;
// is_nothrow_rshift
template <typename T, typename U = T>
using is_nothrow_rshift = details::is_nothrow_rshift_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_rshift_t = typename is_nothrow_rshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_rshift_v = is_nothrow_rshift<T, U>::value;


// increment / decrement

// is_pre_incrementable : ++a
template <typename T>
using is_pre_incrementable = details::is_pre_incrementable_impl<T>;
template <typename T>
using is_pre_incrementable_t = typename is_pre_incrementable<T>::type;
template <typename T>
constexpr bool is_pre_incrementable_v = is_pre_incrementable<T>::value;
// is_nothrow_pre_incrementable
template <typename T>
using is_nothrow_pre_incrementable = details::is_nothrow_pre_incrementable_impl<T>;
template <typename T>
using is_nothrow_pre_incrementable_t = typename is_nothrow_pre_incrementable<T>::type;
template <typename T>
constexpr bool is_nothrow_pre_incrementable_v = is_nothrow_pre_incrementable<T>::value;

// is_post_incrementable : a++
template <typename T>
using is_post_incrementable = details::is_post_incrementable_impl<T>;
template <typename T>
using is_post_incrementable_t = typename is_post_incrementable<T>::type;
template <typename T>
constexpr bool is_post_incrementable_v = is_post_incrementable<T>::value;
// is_nothrow_post_incrementable
template <typename T>
using is_nothrow_post_incrementable = details::is_nothrow_post_incrementable_impl<T>;
template <typename T>
using is_nothrow_post_incrementable_t = typename is_nothrow_post_incrementable<T>::type;
template <typename T>
constexpr bool is_nothrow_post_incrementable_v = is_nothrow_post_incrementable<T>::value;

// is_pre_decrementable : --a
template <typename T>
using is_pre_decrementable = details::is_pre_decrementable_impl<T>;
template <typename T>
using is_pre_decrementable_t = typename is_pre_decrementable<T>::type;
template <typename T>
constexpr bool is_pre_decrementable_v = is_pre_decrementable<T>::value;
// is_nothrow_pre_decrementable
template <typename T>
using is_nothrow_pre_decrementable = details::is_nothrow_pre_decrementable_impl<T>;
template <typename T>
using is_nothrow_pre_decrementable_t = typename is_nothrow_pre_decrementable<T>::type;
template <typename T>
constexpr bool is_nothrow_pre_decrementable_v = is_nothrow_pre_decrementable<T>::value;

// is_post_decrementable : a--
template <typename T>
using is_post_decrementable = details::is_post_decrementable_impl<T>;
template <typename T>
using is_post_decrementable_t = typename is_post_decrementable<T>::type;
template <typename T>
constexpr bool is_post_decrementable_v = is_post_decrementable<T>::value;
// is_nothrow_post_decrementable
template <typename T>
using is_nothrow_post_decrementable = details::is_nothrow_post_decrementable_impl<T>;
template <typename T>
using is_nothrow_post_decrementable_t = typename is_nothrow_post_decrementable<T>::type;
template <typename T>
constexpr bool is_nothrow_post_decrementable_v = is_nothrow_post_decrementable<T>::value;


// comparison

// is_equality : a == b
template <typename T, typename U = T>
using is_equality = details::is_equality_impl<T, U>;
template <typename T, typename U = T>
using is_equality_t = typename is_equality<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_equality_v = is_equality<T, U>::value;
// is_nothrow_equality
template <typename T, typename U = T>
using is_nothrow_equality = details::is_nothrow_equality_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_equality_t = typename is_nothrow_equality<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_equality_v = is_nothrow_equality<T, U>::value;

// is_inequality : a != b
template <typename T, typename U = T>
using is_inequality = details::is_inequality_impl<T, U>;
template <typename T, typename U = T>
using is_inequality_t = typename is_inequality<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_inequality_v = is_inequality<T, U>::value;
// is_nothrow_inequality
template <typename T, typename U = T>
using is_nothrow_inequality = details::is_nothrow_inequality_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_inequality_t = typename is_nothrow_inequality<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_inequality_v = is_nothrow_inequality<T, U>::value;

// is_less_than : a < b
template <typename T, typename U = T>
using is_less_than = details::is_less_than_impl<T, U>;
template <typename T, typename U = T>
using is_less_than_t = typename is_less_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_less_than_v = is_less_than<T, U>::value;
// is_nothrow_less_than
template <typename T, typename U = T>
using is_nothrow_less_than = details::is_nothrow_less_than_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_than_t = typename is_nothrow_less_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_than_v = is_nothrow_less_than<T, U>::value;

// is_less_equal_than : a <= b
template <typename T, typename U = T>
using is_less_equal_than = details::is_less_equal_than_impl<T, U>;
template <typename T, typename U = T>
using is_less_equal_than_t = typename is_less_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_less_equal_than_v = is_less_equal_than<T, U>::value;
// is_nothrow_less_equal_than
template <typename T, typename U = T>
using is_nothrow_less_equal_than = details::is_nothrow_less_equal_than_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_less_equal_than_t = typename is_nothrow_less_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_less_equal_than_v = is_nothrow_less_equal_than<T, U>::value;

// is_greater_than : a > b
template <typename T, typename U = T>
using is_greater_than = details::is_greater_than_impl<T, U>;
template <typename T, typename U = T>
using is_greater_than_t = typename is_greater_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_greater_than_v = is_greater_than<T, U>::value;
// is_nothrow_greater_than
template <typename T, typename U = T>
using is_nothrow_greater_than = details::is_nothrow_greater_than_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_greater_than_t = typename is_nothrow_greater_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_greater_than_v = is_nothrow_greater_than<T, U>::value;

// is_greater_equal_than : a >= b
template <typename T, typename U = T>
using is_greater_equal_than = details::is_greater_equal_than_impl<T, U>;
template <typename T, typename U = T>
using is_greater_equal_than_t = typename is_greater_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_greater_equal_than_v = is_greater_equal_than<T, U>::value;
// is_nothrow_greater_equal_than
template <typename T, typename U = T>
using is_nothrow_greater_equal_than = details::is_nothrow_greater_equal_than_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_greater_equal_than_t = typename is_nothrow_greater_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_greater_equal_than_v = is_nothrow_greater_equal_than<T, U>::value;


// logical

// is_logical_not
template <typename T>
using is_logical_not = details::is_logical_not_impl<T>;
template <typename T>
using is_logical_not_t = typename is_logical_not<T>::type;
template <typename T>
constexpr bool is_logical_not_v = is_logical_not<T>::value;
// is_nothrow_logical_not
template <typename T>
using is_nothrow_logical_not = details::is_nothrow_logical_not_impl<T>;
template <typename T>
using is_nothrow_logical_not_t = typename is_nothrow_logical_not<T>::type;
template <typename T>
constexpr bool is_nothrow_logical_not_v = is_nothrow_logical_not<T>::value;

// is_logical_and
template <typename T, typename U = T>
using is_logical_and = details::is_logical_and_impl<T, U>;
template <typename T, typename U = T>
using is_logical_and_t = typename is_logical_and<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_logical_and_v = is_logical_and<T, U>::value;
// is_nothrow_logical_and
template <typename T, typename U = T>
using is_nothrow_logical_and = details::is_nothrow_logical_and_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_logical_and_t = typename is_nothrow_logical_and<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_logical_and_v = is_nothrow_logical_and<T, U>::value;

// is_logical_or
template <typename T, typename U = T>
using is_logical_or = details::is_logical_or_impl<T, U>;
template <typename T, typename U = T>
using is_logical_or_t = typename is_logical_or<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_logical_or_v = is_logical_or<T, U>::value;
// is_nothrow_logical_or
template <typename T, typename U = T>
using is_nothrow_logical_or = details::is_nothrow_logical_or_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_logical_or_t = typename is_nothrow_logical_or<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_logical_or_v = is_nothrow_logical_or<T, U>::value;


// other

// is_comma
template <typename T, typename U = T>
using is_comma = details::is_comma_impl<T, U>;
template <typename T, typename U = T>
using is_comma_t = typename is_comma<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_comma_v = is_comma<T, U>::value;
// is_nothrow_comma
template <typename T, typename U = T>
using is_nothrow_comma = details::is_nothrow_comma_impl<T, U>;
template <typename T, typename U = T>
using is_nothrow_comma_t = typename is_nothrow_comma<T, U>::type;
template <typename T, typename U = T>
constexpr bool is_nothrow_comma_v = is_nothrow_comma<T, U>::value;

// is_ternary
template <typename B, typename T, typename U = T>
using is_ternary = details::is_ternary_impl<B, T, U>;
template <typename B, typename T, typename U = T>
using is_ternary_t = typename is_ternary<T, U>::type;
template <typename B, typename T, typename U = T>
constexpr bool is_ternary_v = is_ternary<T, U>::value;
// is_nothrow_ternary
template <typename B, typename T, typename U = T>
using is_nothrow_ternary = details::is_nothrow_ternary_impl<B, T, U>;
template <typename B, typename T, typename U = T>
using is_nothrow_ternary_t = typename is_nothrow_ternary<T, U>::type;
template <typename B, typename T, typename U = T>
constexpr bool is_nothrow_ternary_v = is_nothrow_ternary<T, U>::value;

// is_invocable : f(args...)
template <typename F, typename... Args>
using is_invocable = details::is_invocable_impl<details::_holder<F, Args...>>;
template <typename F, typename... Args>
using is_invocable_t = typename is_invocable<F, Args...>::type;
template <typename F, typename... Args>
constexpr bool is_invocable_v = is_invocable<F, Args...>::value;
// is_nothrow_invocable
template <typename F, typename... Args>
using is_nothrow_invocable = details::is_nothrow_invocable_impl<details::_holder<F, Args...>>;
template <typename F, typename... Args>
using is_nothrow_invocable_t = typename is_nothrow_invocable<F, Args...>::type;
template <typename F, typename... Args>
constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<F, Args...>::value;

// is_invocable_r : r f(args...)
template <typename R, typename F, typename... Args>
using is_invocable_r = details::is_invocable_r_impl<details::_holder_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
using is_invocable_r_t = typename is_invocable_r<R, F, Args...>::type;
template <typename R, typename F, typename... Args>
constexpr bool is_invocable_r_v = is_invocable_r<R, F, Args...>::value;
// is_nothrow_invocable_r : r f(args...)
template <typename R, typename F, typename... Args>
using is_nothrow_invocable_r = details::is_nothrow_invocable_r_impl<details::_holder_r<R, F, Args...>>;
template <typename R, typename F, typename... Args>
using is_nothrow_invocable_r_t = typename is_nothrow_invocable_r<R, F, Args...>::type;
template <typename R, typename F, typename... Args>
constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R, F, Args...>::value;

}} // namespace metaprog::traits::utility
