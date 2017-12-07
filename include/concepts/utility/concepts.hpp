#pragma once

#ifndef CONCEPTS_UTILIY_CONCEPTS_HPP_
#define CONCEPTS_UTILIY_CONCEPTS_HPP_

#include "details/concepts_impl.hpp"

namespace concepts { namespace utility {

// validity

// valid
template <typename T>
constexpr bool valid = details::valid_v<T>;


// member access

// dereferenceable
template <typename T>
constexpr bool dereferenceable = details::dereferenceable_v<T>;

// address_of
template <typename T>
constexpr bool address_of = details::address_of_v<T>;

// subscript
template <typename T, typename I>
constexpr bool subscript = details::subscript_v<T, I>;


// assignement

// assignable
template <typename T, typename U = T>
constexpr bool plus_assignable = details::plus_assignable_v<T, U>;

// less_assignable
template <typename T, typename U = T>
constexpr bool less_assignable = details::less_assignable_v<T, U>;

// mult_assignable
template <typename T, typename U = T>
constexpr bool mult_assignable = details::details::mult_assignable_v<T, U>;

// div_assignable
template <typename T, typename U = T>
constexpr bool div_assignable = details::div_assignable_v<T, U>;

// mod_assignable
template <typename T, typename U = T>
constexpr bool mod_assignable = details::mod_assignable_v<T, U>;

// or_assignable
template <typename T, typename U = T>
constexpr bool or_assignable = details::or_assignable_v<T, U>;

// and_assignable
template <typename T, typename U = T>
constexpr bool and_assignable = details::and_assignable_v<T, U>;

// xor_assignable
template <typename T, typename U = T>
constexpr bool xor_assignable = details::xor_assignable_v<T, U>;

// lshift_assignable
template <typename T, typename U = T>
constexpr bool lshift_assignable = details::lshift_assignable_v<T, U>;

// rshift_assignable
template <typename T, typename U = T>
constexpr bool rshift_assignable = details::rshift_assignable_v<T, U>;


// arithmetic

// positive
template <typename T>
constexpr bool positive = details::positive_v<T>;

// negative
template <typename T>
constexpr bool negative = details::negative_v<T>;

// not
template <typename T>
constexpr bool Not = details::not_v<T>;

// plus
template <typename T, typename U = T>
constexpr bool plus = details::plus_v<T, U>;

// less
template <typename T, typename U = T>
constexpr bool less = details::less_v<T, U>;

// mult
template <typename T, typename U = T>
constexpr bool mult = details::mult_v<T, U>;

// div
template <typename T, typename U = T>
constexpr bool div = details::div_v<T, U>;

// mod
template <typename T, typename U = T>
constexpr bool mod = details::mod_v<T, U>;

// and
template <typename T, typename U = T>
constexpr bool And = details::and_v<T, U>;

// or
template <typename T, typename U = T>
constexpr bool Or = details::or_v<T, U>;

// xor
template <typename T, typename U = T>
constexpr bool Xor = details::xor_v<T, U>;

// lshift
template <typename T, typename U = T>
constexpr bool lshift = details::lshift_v<T, U>;

// rshift
template <typename T, typename U = T>
constexpr bool lshift = details::rshift_v<T, U>;


// increment / decrement

// pre_incrementable
template <typename T>
constexpr bool pre_incrementable = details::pre_incrementable_v<T>;

// post_incrementable
template <typename T>
constexpr bool post_incrementable = details::post_incrementable_v<T>;

// pre_decrementable
template <typename T>
constexpr bool pre_decrementable = details::pre_decrementable_v<T>;

// post_decrementable
template <typename T>
constexpr bool post_decrementable = details::post_decrementable_v<T>;


// comparison

// equality
template <typename T, typename U = T>
constexpr bool equality = details::equalityt_v<T, U>;

// inequality
template <typename T, typename U = T>
constexpr bool inequality = details::inequalityt_v<T, U>;

// less_than
template <typename T, typename U = T>
constexpr bool less_than = details::less_thant_v<T, U>;

// less_equal_than
template <typename T, typename U = T>
constexpr bool less_equal_than = details::less_equal_thant_v<T, U>;

// greater_than
template <typename T, typename U = T>
constexpr bool greater_than = details::greater_thant_v<T, U>;

// greater_equal_than
template <typename T, typename U = T>
constexpr bool greater_equal_than = details::greater_equal_thant_v<T, U>;


// other

// function_call
template <typename T, typename... Args>
constexpr bool function_call = details::function_call_v<T, Args...>;

}} // namespace concepts::utility


#endif // CONCEPTS_UTILIY_CONCEPTS_HPP_
