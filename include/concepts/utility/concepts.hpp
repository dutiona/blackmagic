#pragma once

#ifndef CONCEPTS_UTILIY_CONCEPTS_HPP_
#define CONCEPTS_UTILIY_CONCEPTS_HPP_

#include "details/concepts_impl.hpp"

namespace concepts { namespace utility {

// member access

// indirection
template <bool SilentFailure, typename T>
using indirection = details::indirection_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using indirection_t = typename indirection<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool indirection_v = indirection<SilentFailure, T>::value;

// address_of
template <bool SilentFailure, typename T>
using address_of = details::address_of_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using address_of_t = typename address_of<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool address_of_v = address_of<SilentFailure, T>::value;

// subscript
template <bool SilentFailure, typename T, typename I>
using subscript = details::subscript_impl<SilentFailure, T, I>;
template <bool SilentFailure, typename T, typename I>
using subscript_t = typename subscript<SilentFailure, T, I>::type;
template <bool SilentFailure, typename T, typename I>
constexpr bool subscript_v = subscript<SilentFailure, T, I>::value;

// pointer_to_member_of_object
template <bool SilentFailure, typename T, typename I>
using pointer_to_member_of_object = details::pointer_to_member_of_object_impl<SilentFailure, T, I>;
template <bool SilentFailure, typename T, typename I>
using pointer_to_member_of_object_t = typename pointer_to_member_of_object<SilentFailure, T, I>::type;
template <bool SilentFailure, typename T, typename I>
constexpr bool pointer_to_member_of_object_v = pointer_to_member_of_object<SilentFailure, T, I>::value;

// pointer_to_member_of_pointer
template <bool SilentFailure, typename T, typename I>
using pointer_to_member_of_pointer = details::pointer_to_member_of_pointer_impl<SilentFailure, T, I>;
template <bool SilentFailure, typename T, typename I>
using pointer_to_member_of_pointer_t = typename pointer_to_member_of_pointer<SilentFailure, T, I>::type;
template <bool SilentFailure, typename T, typename I>
constexpr bool pointer_to_member_of_pointer_v = pointer_to_member_of_pointer<SilentFailure, T, I>::value;


// assignement

// assignable
template <bool SilentFailure, typename T, typename U = T>
using assignable = details::assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using assignable_t = typename assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool assignable_v = assignable<SilentFailure, T, U>::value;

// plus_assignable
template <bool SilentFailure, typename T, typename U = T>
using plus_assignable = details::plus_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using plus_assignable_t = typename plus_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool plus_assignable_v = plus_assignable<SilentFailure, T, U>::value;

// less_assignable
template <bool SilentFailure, typename T, typename U = T>
using less_assignable = details::less_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using less_assignable_t = typename less_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool less_assignable_v = less_assignable<SilentFailure, T, U>::value;

// mult_assignable
template <bool SilentFailure, typename T, typename U = T>
using mult_assignable = details::mult_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using mult_assignable_t = typename mult_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool mult_assignable_v = mult_assignable<SilentFailure, T, U>::value;

// div_assignable
template <bool SilentFailure, typename T, typename U = T>
using div_assignable = details::div_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using div_assignable_t = typename div_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool div_assignable_v = div_assignable<SilentFailure, T, U>::value;

// mod_assignable
template <bool SilentFailure, typename T, typename U = T>
using mod_assignable = details::mod_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using mod_assignable_t = typename mod_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool mod_assignable_v = mod_assignable<SilentFailure, T, U>::value;

// and_assignable
template <bool SilentFailure, typename T, typename U = T>
using and_assignable = details::and_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using and_assignable_t = typename and_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool and_assignable_v = and_assignable<SilentFailure, T, U>::value;

// or_assignable
template <bool SilentFailure, typename T, typename U = T>
using or_assignable = details::or_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using or_assignable_t = typename or_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool or_assignable_v = or_assignable<SilentFailure, T, U>::value;

// xor_assignable
template <bool SilentFailure, typename T, typename U = T>
using xor_assignable = details::xor_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using xor_assignable_t = typename xor_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool xor_assignable_v = xor_assignable<SilentFailure, T, U>::value;

// lshift_assignable
template <bool SilentFailure, typename T, typename U = T>
using lshift_assignable = details::lshift_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using lshift_assignable_t = typename lshift_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool lshift_assignable_v = lshift_assignable<SilentFailure, T, U>::value;

// rshift_assignable
template <bool SilentFailure, typename T, typename U = T>
using rshift_assignable = details::rshift_assignable_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using rshift_assignable_t = typename rshift_assignable<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool rshift_assignable_v = rshift_assignable<SilentFailure, T, U>::value;


// arithmetic

// positive
template <bool SilentFailure, typename T>
using positive = details::positive_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using positive_t = typename positive<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool positive_v = positive<SilentFailure, T>::value;

// negative
template <bool SilentFailure, typename T>
using negative = details::negative_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using negative_t = typename negative<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool negative_v = negative<SilentFailure, T>::value;

// not
template <bool SilentFailure, typename T>
using Not = details::not_impl<SilentFailure, T>; // "not" is a c++ keyword
template <bool SilentFailure, typename T>
using not_t = typename Not<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool not_v = Not<SilentFailure, T>::value;

// plus
template <bool SilentFailure, typename T, typename U = T>
using plus = details::plus_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using plus_t = typename plus<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool plus_v = plus<SilentFailure, T, U>::value;

// less
template <bool SilentFailure, typename T, typename U = T>
using less = details::less_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using less_t = typename less<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool less_v = less<SilentFailure, T, U>::value;

// mult
template <bool SilentFailure, typename T, typename U = T>
using mult = details::mult_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using mult_t = typename mult<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool mult_v = mult<SilentFailure, T, U>::value;

// div
template <bool SilentFailure, typename T, typename U = T>
using div = details::div_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using div_t = typename div<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool div_v = div<SilentFailure, T, U>::value;

// mod
template <bool SilentFailure, typename T, typename U = T>
using mod = details::mod_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using mod_t = typename mod<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool mod_v = mod<SilentFailure, T, U>::value;

// and
template <bool SilentFailure, typename T, typename U = T>
using And = details::and_impl<SilentFailure, T, U>; // "and" is a c++ keyword
template <bool SilentFailure, typename T, typename U = T>
using and_t = typename And<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool and_v = And<SilentFailure, T, U>::value;

// or
template <bool SilentFailure, typename T, typename U = T>
using Or = details::or_impl<SilentFailure, T, U>; // "or" is a c++ keyword
template <bool SilentFailure, typename T, typename U = T>
using or_t = typename Or<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool or_v = Or<SilentFailure, T, U>::value;

// xor
template <bool SilentFailure, typename T, typename U = T>
using Xor = details::xor_impl<SilentFailure, T, U>; // "xor" is a c++ keyword
template <bool SilentFailure, typename T, typename U = T>
using xor_t = typename Xor<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool xor_v = Xor<SilentFailure, T, U>::value;

// lshift
template <bool SilentFailure, typename T, typename U = T>
using lshift = details::lshift_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using lshift_t = typename lshift<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool lshift_v = lshift<SilentFailure, T, U>::value;

// rshift
template <bool SilentFailure, typename T, typename U = T>
using rshift = details::rshift_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using rshift_t = typename rshift<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool rshift_v = rshift<SilentFailure, T, U>::value;


// increment / decrement

// pre_incrementable
template <bool SilentFailure, typename T>
using pre_incrementable = details::pre_incrementable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using pre_incrementable_t = typename pre_incrementable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool pre_incrementable_v = pre_incrementable<SilentFailure, T>::value;

// post_incrementable
template <bool SilentFailure, typename T>
using post_incrementable = details::post_incrementable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using post_incrementable_t = typename post_incrementable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool post_incrementable_v = post_incrementable<SilentFailure, T>::value;

// pre_decrementable
template <bool SilentFailure, typename T>
using pre_decrementable = details::pre_decrementable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using pre_decrementable_t = typename pre_decrementable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool pre_decrementable_v = pre_decrementable<SilentFailure, T>::value;

// post_decrementable
template <bool SilentFailure, typename T>
using post_decrementable = details::post_decrementable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using post_decrementable_t = typename post_decrementable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool post_decrementable_v = post_decrementable<SilentFailure, T>::value;


// comparison

// equality
template <bool SilentFailure, typename T, typename U = T>
using equality = details::equality_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using equality_t = typename equality<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool equality_v = equality<SilentFailure, T, U>::value;

// inequality
template <bool SilentFailure, typename T, typename U = T>
using inequality = details::inequality_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using inequality_t = typename inequality<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool inequality_v = inequality<SilentFailure, T, U>::value;

// less_than
template <bool SilentFailure, typename T, typename U = T>
using less_than = details::less_than_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using less_than_t = typename less_than<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool less_than_v = less_than<SilentFailure, T, U>::value;

// less_equal_than
template <bool SilentFailure, typename T, typename U = T>
using less_equal_than = details::less_equal_than_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using less_equal_than_t = typename less_equal_than<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool less_equal_than_v = less_equal_than<SilentFailure, T, U>::value;

// greater_than
template <bool SilentFailure, typename T, typename U = T>
using greater_than = details::greater_than_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using greater_than_t = typename greater_than<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool greater_than_v = greater_than<SilentFailure, T, U>::value;

// greater_equal_than
template <bool SilentFailure, typename T, typename U = T>
using greater_equal_than = details::greater_equal_than_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using greater_equal_than_t = typename greater_equal_than<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool greater_equal_than_v = greater_equal_than<SilentFailure, T, U>::value;


// logical

// logical_not
template <bool SilentFailure, typename T>
using logical_not = details::logical_not_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using logical_not_t = typename logical_not<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool logical_not_v = logical_not<SilentFailure, T>::value;

// logical_and
template <bool SilentFailure, typename T, typename U = T>
using logical_and = details::logical_and_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using logical_and_t = typename logical_and<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool logical_and_v = logical_and<SilentFailure, T, U>::value;

// logical_or
template <bool SilentFailure, typename T, typename U = T>
using logical_or = details::logical_or_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using logical_or_t = typename logical_or<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool logical_or_v = logical_or<SilentFailure, T, U>::value;


// other

// comma
template <bool SilentFailure, typename T, typename U = T>
using comma = details::comma_impl<SilentFailure, T, U>;
template <bool SilentFailure, typename T, typename U = T>
using comma_t = typename comma<SilentFailure, T, U>::type;
template <bool SilentFailure, typename T, typename U = T>
constexpr bool comma_v = comma<SilentFailure, T, U>::value;

// ternary
template <bool SilentFailure, typename B, typename T, typename U = T>
using ternary = details::ternary_impl<SilentFailure, B, T, U>;
template <bool SilentFailure, typename B, typename T, typename U = T>
using ternary_t = typename ternary<SilentFailure, B, T, U>::type;
template <bool SilentFailure, typename B, typename T, typename U = T>
constexpr bool ternary_v = ternary<SilentFailure, B, T, U>::value;

// invocable
template <bool SilentFailure, typename F, typename... Args>
using invocable = details::invocable_impl<SilentFailure, details::_holder<F, Args...>>;
template <bool SilentFailure, typename F, typename... Args>
using invocable_t = typename invocable<SilentFailure, F, Args...>::type;
template <bool SilentFailure, typename F, typename... Args>
constexpr bool invocable_v = invocable<SilentFailure, F, Args...>::value;

// invocable r
template <bool SilentFailure, typename R, typename F, typename... Args>
using invocable_r = details::invocable_r_impl<SilentFailure, details::_holder_r<R, F, Args...>>;
template <bool SilentFailure, typename R, typename F, typename... Args>
using invocable_r_t = typename invocable_r<SilentFailure, R, F, Args...>::type;
template <bool SilentFailure, typename R, typename F, typename... Args>
constexpr bool invocable_r_v = invocable_r<SilentFailure, R, F, Args...>::value;

}} // namespace concepts::utility


#endif // CONCEPTS_UTILIY_CONCEPTS_HPP_
