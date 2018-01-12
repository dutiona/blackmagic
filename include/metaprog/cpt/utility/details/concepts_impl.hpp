#pragma once

#ifndef METAPROG_CPT_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
#define METAPROG_CPT_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_

#include "../traits.hpp"

#include "../../core.hpp"

#include <type_traits>

namespace cpt { namespace concepts { namespace utility { namespace details {

namespace traits = traits::utility;

// member access

// indirection
template <typename T>
using indirection_impl = make_predicate<make_condition<traits::is_indirection_v<T>>>;

// address_of
template <typename T>
using address_of_impl = make_predicate<make_condition<traits::is_address_of_v<T>>>;

// subscript
template <typename T, typename I>
using subscript_impl = make_predicate<make_condition<traits::is_subscript_v<T, I>>>;

// pointer_to_member_of_object
template <typename T, typename I>
using pointer_to_member_of_object_impl = make_predicate<make_condition<traits::is_pointer_to_member_of_object_v<T, I>>>;

// pointer_to_member_of_pointer
template <typename T, typename I>
using pointer_to_member_of_pointer_impl =
  make_predicate<make_condition<traits::is_pointer_to_member_of_pointer_v<T, I>>>;


// assignement

// assignable
template <typename T, typename U = T>
using assignable_impl = make_predicate<make_condition<traits::is_assignable_v<T, U>>>;

// plus_assignable
template <typename T, typename U = T>
using plus_assignable_impl = make_predicate<make_condition<traits::is_plus_assignable_v<T, U>>>;

// less_assignable
template <typename T, typename U = T>
using less_assignable_impl = make_predicate<make_condition<traits::is_less_assignable_v<T, U>>>;

// mult_assignable
template <typename T, typename U = T>
using mult_assignable_impl = make_predicate<make_condition<traits::is_mult_assignable_v<T, U>>>;

// div_assignable
template <typename T, typename U = T>
using div_assignable_impl = make_predicate<make_condition<traits::is_div_assignable_v<T, U>>>;

// mod_assignable
template <typename T, typename U = T>
using mod_assignable_impl = make_predicate<make_condition<traits::is_mod_assignable_v<T, U>>>;

// or_assignable
template <typename T, typename U = T>
using or_assignable_impl = make_predicate<make_condition<traits::is_or_assignable_v<T, U>>>;

// and_assignable
template <typename T, typename U = T>
using and_assignable_impl = make_predicate<make_condition<traits::is_and_assignable_v<T, U>>>;

// xor_assignable
template <typename T, typename U = T>
using xor_assignable_impl = make_predicate<make_condition<traits::is_xor_assignable_v<T, U>>>;

// lshift_assignable
template <typename T, typename U = T>
using lshift_assignable_impl = make_predicate<make_condition<traits::is_lshift_assignable_v<T, U>>>;

// rshift_assignable
template <typename T, typename U = T>
using rshift_assignable_impl = make_predicate<make_condition<traits::is_rshift_assignable_v<T, U>>>;


// arithmetic

// positive
template <typename T>
using positive_impl = make_predicate<make_condition<traits::is_positive_v<T>>>;

// negative
template <typename T>
using negative_impl = make_predicate<make_condition<traits::is_negative_v<T>>>;

// not
template <typename T>
using not_impl = make_predicate<make_condition<traits::is_not_v<T>>>;

// plus
template <typename T, typename U = T>
using plus_impl = make_predicate<make_condition<traits::is_plus_v<T, U>>>;

// less
template <typename T, typename U = T>
using less_impl = make_predicate<make_condition<traits::is_less_v<T, U>>>;

// mult
template <typename T, typename U = T>
using mult_impl = make_predicate<make_condition<traits::is_mult_v<T, U>>>;

// div
template <typename T, typename U = T>
using div_impl = make_predicate<make_condition<traits::is_div_v<T, U>>>;

// mod
template <typename T, typename U = T>
using mod_impl = make_predicate<make_condition<traits::is_mod_v<T, U>>>;

// and
template <typename T, typename U = T>
using and_impl = make_predicate<make_condition<traits::is_and_v<T, U>>>;

// or
template <typename T, typename U = T>
using or_impl = make_predicate<make_condition<traits::is_or_v<T, U>>>;

// xor
template <typename T, typename U = T>
using xor_impl = make_predicate<make_condition<traits::is_xor_v<T, U>>>;

// lshift
template <typename T, typename U = T>
using lshift_impl = make_predicate<make_condition<traits::is_lshift_v<T, U>>>;

// rshift
template <typename T, typename U = T>
using rshift_impl = make_predicate<make_condition<traits::is_rshift_v<T, U>>>;


// increment / decrement

// pre_incrementable
template <typename T>
using pre_incrementable_impl = make_predicate<make_condition<traits::is_pre_incrementable_v<T>>>;

// post_incrementable
template <typename T>
using post_incrementable_impl = make_predicate<make_condition<traits::is_post_incrementable_v<T>>>;

// pre_decrementable
template <typename T>
using pre_decrementable_impl = make_predicate<make_condition<traits::is_pre_decrementable_v<T>>>;

// post_decrementable
template <typename T>
using post_decrementable_impl = make_predicate<make_condition<traits::is_post_decrementable_v<T>>>;


// comparison

// equality
template <typename T, typename U = T>
using equality_impl = make_predicate<make_condition<traits::is_equality_v<T, U>>>;

// inequality
template <typename T, typename U = T>
using inequality_impl = make_predicate<make_condition<traits::is_inequality_v<T, U>>>;

// less_than
template <typename T, typename U = T>
using less_than_impl = make_predicate<make_condition<traits::is_less_than_v<T, U>>>;

// less_equal_than
template <typename T, typename U = T>
using less_equal_than_impl = make_predicate<make_condition<traits::is_less_equal_than_v<T, U>>>;

// greater_than
template <typename T, typename U = T>
using greater_than_impl = make_predicate<make_condition<traits::is_greater_than_v<T, U>>>;

// greater_equal_than
template <typename T, typename U = T>
using greater_equal_than_impl = make_predicate<make_condition<traits::is_greater_equal_than_v<T, U>>>;


// logical

// logical_not
template <typename T>
using logical_not_impl = make_predicate<make_condition<traits::is_logical_not_v<T>>>;

// logical_and
template <typename T, typename U = T>
using logical_and_impl = make_predicate<make_condition<traits::is_logical_and_v<T, U>>>;

// logical_or
template <typename T, typename U = T>
using logical_or_impl = make_predicate<make_condition<traits::is_logical_or_v<T, U>>>;


// other

// comma
template <typename T, typename U = T>
using comma_impl = make_predicate<make_condition<traits::is_comma_v<T, U>>>;

// ternary
template <typename B, typename T, typename U = T>
using ternary_impl = make_predicate<make_condition<traits::is_ternary_v<B, T, U>>>;

// invocable
template <typename F, typename... Args>
using invocable_impl = make_predicate<make_condition<traits::is_invocable_v<F, Args...>>>;

// invocable r
template <typename R, typename F, typename... Args>
using invocable_r_impl = make_predicate<make_condition<traits::is_invocable_r_v<R, F, Args...>>>;

}}}} // namespace cpt::concepts::utility::details


#endif // METAPROG_CPT_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
