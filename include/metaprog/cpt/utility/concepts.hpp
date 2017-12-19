#pragma once

#ifndef METAPROG_CPT_UTILIY_CONCEPTS_HPP_
#define METAPROG_CPT_UTILIY_CONCEPTS_HPP_

#include "details/concepts_impl.hpp"

namespace cpt { namespace concepts { namespace utility {

// member access

// indirection
struct indirection {
  template <bool SilentFailure, typename T>
  using type = details::indirection_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// address_of
struct address_of {
  template <bool SilentFailure, typename T>
  using type = details::address_of_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};


// subscript
struct subscript {
  template <bool SilentFailure, typename T, typename I>
  using type = details::subscript_impl<SilentFailure, T, I>;
  template <bool SilentFailure, typename T, typename I>
  using underlying_type = typename type<SilentFailure, T, I>::type;
  template <bool SilentFailure, typename T, typename I>
  static constexpr bool value = type<SilentFailure, T, I>::value;
};

// pointer_to_member_of_object
struct pointer_to_member_of_object {
  template <bool SilentFailure, typename T, typename I>
  using type = details::pointer_to_member_of_object_impl<SilentFailure, T, I>;
  template <bool SilentFailure, typename T, typename I>
  using underlying_type = typename type<SilentFailure, T, I>::type;
  template <bool SilentFailure, typename T, typename I>
  static constexpr bool value = type<SilentFailure, T, I>::value;
};


// pointer_to_member_of_pointer
struct pointer_to_member_of_pointer {
  template <bool SilentFailure, typename T, typename I>
  using type = details::pointer_to_member_of_pointer_impl<SilentFailure, T, I>;
  template <bool SilentFailure, typename T, typename I>
  using underlying_type = typename type<SilentFailure, T, I>::type;
  template <bool SilentFailure, typename T, typename I>
  static constexpr bool value = type<SilentFailure, T, I>::value;
};


// assignement

// assignable
struct assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// plus_assignable
struct plus_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::plus_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// less_assignable
struct less_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::less_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// mult_assignable
struct mult_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::mult_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// div_assignable
struct div_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::div_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using div_assignable_t = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// mod_assignable
struct mod_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::mod_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// and_assignable
struct and_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::and_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// or_assignable
struct or_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::or_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// xor_assignable
struct xor_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::xor_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// lshift_assignable
struct lshift_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::lshift_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// rshift_assignable
struct rshift_assignable {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::rshift_assignable_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};


// arithmetic

// positive
struct positive {
  template <bool SilentFailure, typename T>
  using type = details::positive_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// negative
struct negative {
  template <bool SilentFailure, typename T>
  using type = details::negative_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// not
struct Not { // "not" is a c++ keyword
  template <bool SilentFailure, typename T>
  using type = details::not_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// plus
struct plus {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::plus_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// less
struct less {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::less_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// mult
struct mult {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::mult_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// div
struct div {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::div_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// mod
struct mod {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::mod_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// and
struct And { // "and" is a c++ keyword
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::and_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// or
struct Or { // "or" is a c++ keyword
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::or_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// xor
struct Xor { // "xor" is a c++ keyword
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::xor_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// lshift
struct lshift {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::lshift_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// rshift
struct rshift {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::rshift_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};


// increment / decrement

// pre_incrementable
struct pre_incrementable {
  template <bool SilentFailure, typename T>
  using type = details::pre_incrementable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// post_incrementable
struct post_incrementable {
  template <bool SilentFailure, typename T>
  using type = details::post_incrementable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// pre_decrementable
struct pre_decrementable {
  template <bool SilentFailure, typename T>
  using type = details::pre_decrementable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// post_decrementable
struct post_decrementable {
  template <bool SilentFailure, typename T>
  using type = details::post_decrementable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};


// comparison

// equality
struct equality {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::equality_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// inequality
struct inequality {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::inequality_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// less_than
struct less_than {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::less_than_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// less_equal_than
struct less_equal_than {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::less_equal_than_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// greater_than
struct greater_than {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::greater_than_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// greater_equal_than
struct greater_equal_than {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::greater_equal_than_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};


// logical

// logical_not
struct logical_not {
  template <bool SilentFailure, typename T>
  using type = details::logical_not_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// logical_and
struct logical_and {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::logical_and_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// logical_or
struct logical_or {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::logical_or_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};


// other

// comma
struct comma {
  template <bool SilentFailure, typename T, typename U = T>
  using type = details::comma_impl<SilentFailure, T, U>;
  template <bool SilentFailure, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, T, U>::type;
  template <bool SilentFailure, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, T, U>::value;
};

// ternary
struct ternary {
  template <bool SilentFailure, typename B, typename T, typename U = T>
  using type = details::ternary_impl<SilentFailure, B, T, U>;
  template <bool SilentFailure, typename B, typename T, typename U = T>
  using underlying_type = typename type<SilentFailure, B, T, U>::type;
  template <bool SilentFailure, typename B, typename T, typename U = T>
  static constexpr bool value = type<SilentFailure, B, T, U>::value;
};

// invocable
struct invocable {
  template <bool SilentFailure, typename F, typename... Args>
  using type = details::invocable_impl<SilentFailure, details::_holder<F, Args...>>;
  template <bool SilentFailure, typename F, typename... Args>
  using underlying_type = typename type<SilentFailure, F, Args...>::type;
  template <bool SilentFailure, typename F, typename... Args>
  static constexpr bool value = type<SilentFailure, F, Args...>::value;
};

// invocable r
struct invocable_r {
  template <bool SilentFailure, typename R, typename F, typename... Args>
  using type = details::invocable_r_impl<SilentFailure, details::_holder_r<R, F, Args...>>;
  template <bool SilentFailure, typename R, typename F, typename... Args>
  using underlying_type = typename type<SilentFailure, R, F, Args...>::type;
  template <bool SilentFailure, typename R, typename F, typename... Args>
  static constexpr bool value = type<SilentFailure, R, F, Args...>::value;
};

}}} // namespace cpt::concepts::utility


#endif // METAPROG_CPT_UTILIY_CONCEPTS_HPP_
