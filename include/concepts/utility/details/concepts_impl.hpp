#pragma once

#ifndef CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_

#include <concepts/utility/traits.hpp>

#include <type_traits>

namespace concepts { namespace utility { namespace details {

namespace traits = traits::utility;

// validity

// valid
template <typename T, typename = void>
struct valid_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the valid concept.");
};
template <typename T>
struct valid_impl<T, std::enable_if_t<std::disjunction_v<traits::is_valid<T>, traits::is_nothrow_valid<T>>>>
  : std::true_type {
};
template <typename T>
using valid = valid_impl<T>;
template <typename T>
using valid_t = typename valid<T>::type;
template <typename T>
constexpr bool valid_v = valid<T>::value;


// member access

// dereferenceable
template <typename T, typename = void>
struct dereferenceable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the dereferenceable concept.");
};
template <typename T>
struct dereferenceable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_dereferenceable<T>, traits::is_nothrow_dereferenceable<T>>>>
  : std::true_type {
};
template <typename T>
using dereferenceable = dereferenceable_impl<T>;
template <typename T>
using dereferenceable_t = typename dereferenceable<T>::type;
template <typename T>
constexpr bool dereferenceable_v = dereferenceable<T>::value;

// address_of
template <typename T, typename = void>
struct address_of_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the address of concept.");
};
template <typename T>
struct address_of_impl<T,
                       std::enable_if_t<std::disjunction_v<traits::is_address_of<T>, traits::is_nothrow_address_of<T>>>>
  : std::true_type {
};
template <typename T>
using address_of = address_of_impl<T>;
template <typename T>
using address_of_t = typename address_of<T>::type;
template <typename T>
constexpr bool address_of_v = address_of<T>::value;

// subscript
template <typename T, typename I, typename = void>
struct subscript_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the subscript concept.");
};
template <typename T, typename I>
struct subscript_impl<
  T, I, std::enable_if_t<std::disjunction_v<traits::is_subscript<T, I>, traits::is_nothrow_subscript<T, I>>>>
  : std::true_type {
};
template <typename T, typename I>
using subscript = subscript_impl<T, I>;
template <typename T, typename I>
using subscript_t = typename subscript<T, I>::type;
template <typename T, typename I>
constexpr bool subscript_v = subscript<T, I>::value;


// assignement

// assignable
template <typename T, typename U = T, typename = void>
struct assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the assignable concept.");
};
template <typename T, typename U>
struct assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_assignable<T, U>, traits::is_nothrow_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using assignable = assignable_impl<T, U>;
template <typename T, typename U = T>
using assignable_t = typename assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool assignable_v = assignable<T, U>::value;

// plus_assignable
template <typename T, typename U = T, typename = void>
struct plus_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the plus assignable concept.");
};
template <typename T, typename U>
struct plus_assignable_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_plus_assignable<T, U>, traits::is_nothrow_plus_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using plus_assignable = plus_assignable_impl<T, U>;
template <typename T, typename U = T>
using plus_assignable_t = typename plus_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool plus_assignable_v = plus_assignable<T, U>::value;

// less_assignable
template <typename T, typename U = T, typename = void>
struct less_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the less assignable concept.");
};
template <typename T, typename U>
struct less_assignable_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_less_assignable<T, U>, traits::is_nothrow_less_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using less_assignable = less_assignable_impl<T, U>;
template <typename T, typename U = T>
using less_assignable_t = typename less_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool less_assignable_v = less_assignable<T, U>::value;

// mult_assignable
template <typename T, typename U = T, typename = void>
struct mult_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the mult assignable concept.");
};
template <typename T, typename U>
struct mult_assignable_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_mult_assignable<T, U>, traits::is_nothrow_mult_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using mult_assignable = mult_assignable_impl<T, U>;
template <typename T, typename U = T>
using mult_assignable_t = typename mult_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool mult_assignable_v = mult_assignable<T, U>::value;

// div_assignable
template <typename T, typename U = T, typename = void>
struct div_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the div assignable concept.");
};
template <typename T, typename U>
struct div_assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_div_assignable<T, U>, traits::is_nothrow_div_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using div_assignable = div_assignable_impl<T, U>;
template <typename T, typename U = T>
using div_assignable_t = typename div_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool div_assignable_v = div_assignable<T, U>::value;

// mod_assignable
template <typename T, typename U = T, typename = void>
struct mod_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the mod assignable concept.");
};
template <typename T, typename U>
struct mod_assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_mod_assignable<T, U>, traits::is_nothrow_mod_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using mod_assignable = mod_assignable_impl<T, U>;
template <typename T, typename U = T>
using mod_assignable_t = typename mod_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool mod_assignable_v = mod_assignable<T, U>::value;

// or_assignable
template <typename T, typename U = T, typename = void>
struct or_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the or assignable concept.");
};
template <typename T, typename U>
struct or_assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_or_assignable<T, U>, traits::is_nothrow_or_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using or_assignable = or_assignable_impl<T, U>;
template <typename T, typename U = T>
using or_assignable_t = typename or_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool or_assignable_v = or_assignable<T, U>::value;

// and_assignable
template <typename T, typename U = T, typename = void>
struct and_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the and assignable concept.");
};
template <typename T, typename U>
struct and_assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_and_assignable<T, U>, traits::is_nothrow_and_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using and_assignable = and_assignable_impl<T, U>;
template <typename T, typename U = T>
using and_assignable_t = typename and_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool and_assignable_v = and_assignable<T, U>::value;

// xor_assignable
template <typename T, typename U = T, typename = void>
struct xor_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the xor assignable concept.");
};
template <typename T, typename U>
struct xor_assignable_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_xor_assignable<T, U>, traits::is_nothrow_xor_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using xor_assignable = xor_assignable_impl<T, U>;
template <typename T, typename U = T>
using xor_assignable_t = typename xor_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool xor_assignable_v = xor_assignable<T, U>::value;

// lshift_assignable
template <typename T, typename U = T, typename = void>
struct lshift_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the lshift assignable concept.");
};
template <typename T, typename U>
struct lshift_assignable_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_lshift_assignable<T, U>, traits::is_nothrow_lshift_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using lshift_assignable = lshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using lshift_assignable_t = typename lshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool lshift_assignable_v = lshift_assignable<T, U>::value;

// rshift_assignable
template <typename T, typename U = T, typename = void>
struct rshift_assignable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the rshift assignable concept.");
};
template <typename T, typename U>
struct rshift_assignable_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_rshift_assignable<T, U>, traits::is_nothrow_rshift_assignable<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using rshift_assignable = rshift_assignable_impl<T, U>;
template <typename T, typename U = T>
using rshift_assignable_t = typename rshift_assignable<T, U>::type;
template <typename T, typename U = T>
constexpr bool rshift_assignable_v = rshift_assignable<T, U>::value;


// arithmetic

// positive
template <typename T, typename = void>
struct positive_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the positive concept.");
};
template <typename T>
struct positive_impl<T, std::enable_if_t<std::disjunction_v<traits::is_positive<T>, traits::is_nothrow_positive<T>>>>
  : std::true_type {
};
template <typename T>
using positive = positive_impl<T>;
template <typename T>
using positive_t = typename positive<T>::type;
template <typename T>
constexpr bool positive_v = positive<T>::value;

// negative
template <typename T, typename = void>
struct negative_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the negative concept.");
};
template <typename T>
struct negative_impl<T, std::enable_if_t<std::disjunction_v<traits::is_negative<T>, traits::is_nothrow_negative<T>>>>
  : std::true_type {
};
template <typename T>
using negative = negative_impl<T>;
template <typename T>
using negative_t = typename negative<T>::type;
template <typename T>
constexpr bool negative_v = negative<T>::value;

// not
template <typename T, typename = void>
struct not_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the not concept.");
};
template <typename T>
struct not_impl<T, std::enable_if_t<std::disjunction_v<traits::is_not<T>, traits::is_nothrow_not<T>>>>
  : std::true_type {
};
template <typename T>
using Not = not_impl<T>; // "not" is a c++ keyword
template <typename T>
using not_t = typename Not<T>::type;
template <typename T>
constexpr bool not_v = Not<T>::value;

// plus
template <typename T, typename U = T, typename = void>
struct plus_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the plus concept.");
};
template <typename T, typename U>
struct plus_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_plus<T, U>, traits::is_nothrow_plus<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using plus = plus_impl<T, U>;
template <typename T, typename U = T>
using plus_t = typename plus<T, U>::type;
template <typename T, typename U = T>
constexpr bool plus_v = plus<T, U>::value;

// less
template <typename T, typename U = T, typename = void>
struct less_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the less concept.");
};
template <typename T, typename U>
struct less_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_less<T, U>, traits::is_nothrow_less<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using less = less_impl<T, U>;
template <typename T, typename U = T>
using less_t = typename less<T, U>::type;
template <typename T, typename U = T>
constexpr bool less_v = less<T, U>::value;

// mult
template <typename T, typename U = T, typename = void>
struct mult_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the mult concept.");
};
template <typename T, typename U>
struct mult_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_mult<T, U>, traits::is_nothrow_mult<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using mult = mult_impl<T, U>;
template <typename T, typename U = T>
using mult_t = typename mult<T, U>::type;
template <typename T, typename U = T>
constexpr bool mult_v = mult<T, U>::value;

// div
template <typename T, typename U = T, typename = void>
struct div_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the div concept.");
};
template <typename T, typename U>
struct div_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_div<T, U>, traits::is_nothrow_div<T, U>>>>
  : std::true_type {
};
template <typename T, typename U>
using div = div_impl<T, U>;
template <typename T, typename U = T>
using div_t = typename div<T, U>::type;
template <typename T, typename U = T>
constexpr bool div_v = div<T, U>::value;

// mod
template <typename T, typename U = T, typename = void>
struct mod_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the mod concept.");
};
template <typename T, typename U>
struct mod_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_mod<T, U>, traits::is_nothrow_mod<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using mod = mod_impl<T, U>;
template <typename T, typename U = T>
using mod_t = typename mod<T, U>::type;
template <typename T, typename U = T>
constexpr bool mod_v = mod<T, U>::value;

// and
template <typename T, typename U = T, typename = void>
struct and_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the and concept.");
};
template <typename T, typename U>
struct and_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_and<T, U>, traits::is_nothrow_and<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using And = and_impl<T, U>; // "and" is a c++ keyword
template <typename T, typename U = T>
using and_t = typename And<T, U>::type;
template <typename T, typename U = T>
constexpr bool and_v = And<T, U>::value;

// or
template <typename T, typename U = T, typename = void>
struct or_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the or concept.");
};
template <typename T, typename U>
struct or_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_or<T, U>, traits::is_nothrow_or<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using Or = or_impl<T, U>; // "or" is a c++ keyword
template <typename T, typename U = T>
using or_t = typename Or<T, U>::type;
template <typename T, typename U = T>
constexpr bool or_v = Or<T, U>::value;

// xor
template <typename T, typename U = T, typename = void>
struct xor_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the xor concept.");
};
template <typename T, typename U>
struct xor_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_xor<T, U>, traits::is_nothrow_xor<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using Xor = xor_impl<T, U>; // "xor" is a c++ keyword
template <typename T, typename U = T>
using xor_t = typename Xor<T, U>::type;
template <typename T, typename U = T>
constexpr bool xor_v = Xor<T, U>::value;

// lshift
template <typename T, typename U = T, typename = void>
struct lshift_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the lshift concept.");
};
template <typename T, typename U>
struct lshift_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_lshift<T, U>, traits::is_nothrow_lshift<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using lshift = lshift_impl<T, U>;
template <typename T, typename U = T>
using lshift_t = typename lshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool lshift_v = lshift<T, U>::value;

// rshift
template <typename T, typename U = T, typename = void>
struct rshift_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the rshift concept.");
};
template <typename T, typename U>
struct rshift_impl<T, U, std::enable_if_t<std::disjunction_v<traits::is_rshift<T, U>, traits::is_nothrow_rshift<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using rshift = rshift_impl<T, U>;
template <typename T, typename U = T>
using rshift_t = typename rshift<T, U>::type;
template <typename T, typename U = T>
constexpr bool rshift_v = rshift<T, U>::value;


// increment / decrement

// pre_incrementable
template <typename T, typename = void>
struct pre_incrementable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the pre incrementable concept.");
};
template <typename T>
struct pre_incrementable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_pre_incrementable<T>, traits::is_nothrow_pre_incrementable<T>>>>
  : std::true_type {
};
template <typename T>
using pre_incrementable = pre_incrementable_impl<T>;
template <typename T>
using pre_incrementable_t = typename pre_incrementable<T>::type;
template <typename T>
constexpr bool pre_incrementable_v = pre_incrementable<T>::value;

// post_incrementable
template <typename T, typename = void>
struct post_incrementable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the post incrementable concept.");
};
template <typename T>
struct post_incrementable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_post_incrementable<T>, traits::is_nothrow_post_incrementable<T>>>>
  : std::true_type {
};
template <typename T>
using post_incrementable = post_incrementable_impl<T>;
template <typename T>
using post_incrementable_t = typename post_incrementable<T>::type;
template <typename T>
constexpr bool post_incrementable_v = post_incrementable<T>::value;

// pre_decrementable
template <typename T, typename = void>
struct pre_decrementable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the pre decrementable concept.");
};
template <typename T>
struct pre_decrementable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_pre_decrementable<T>, traits::is_nothrow_pre_decrementable<T>>>>
  : std::true_type {
};
template <typename T>
using pre_decrementable = pre_decrementable_impl<T>;
template <typename T>
using pre_decrementable_t = typename pre_decrementable<T>::type;
template <typename T>
constexpr bool pre_decrementable_v = pre_decrementable<T>::value;

// post_decrementable
template <typename T, typename = void>
struct post_decrementable_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the post decrementable concept.");
};
template <typename T>
struct post_decrementable_impl<
  T, std::enable_if_t<std::disjunction_v<traits::is_post_decrementable<T>, traits::is_nothrow_post_decrementable<T>>>>
  : std::true_type {
};
template <typename T>
using post_decrementable = post_decrementable_impl<T>;
template <typename T>
using post_decrementable_t = typename post_decrementable<T>::type;
template <typename T>
constexpr bool post_decrementable_v = post_decrementable<T>::value;


// comparison

// equality
template <typename T, typename U = T, typename = void>
struct equality_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the equality concept.");
};
template <typename T, typename U>
struct equality_impl<T, U,
                     std::enable_if_t<std::disjunction_v<traits::is_equality<T, U>, traits::is_nothrow_equality<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using equality = equality_impl<T, U>;
template <typename T, typename U = T>
using equality_t = typename equality<T, U>::type;
template <typename T, typename U = T>
constexpr bool equality_v = equality<T, U>::value;

// inequality
template <typename T, typename U = T, typename = void>
struct inequality_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the inequality concept.");
};
template <typename T, typename U>
struct inequality_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_inequality<T, U>, traits::is_nothrow_inequality<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using inequality = inequality_impl<T, U>;
template <typename T, typename U = T>
using inequality_t = typename inequality<T, U>::type;
template <typename T, typename U = T>
constexpr bool inequality_v = inequality<T, U>::value;

// less_than
template <typename T, typename U = T, typename = void>
struct less_than_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the less than concept.");
};
template <typename T, typename U>
struct less_than_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_less_than<T, U>, traits::is_nothrow_less_than<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using less_than = less_than_impl<T, U>;
template <typename T, typename U = T>
using less_than_t = typename less_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool less_than_v = less_than<T, U>::value;

// less_equal_than
template <typename T, typename U = T, typename = void>
struct less_equal_than_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the less equal than concept.");
};
template <typename T, typename U>
struct less_equal_than_impl<
  T, U,
  std::enable_if_t<std::disjunction_v<traits::is_less_equal_than<T, U>, traits::is_nothrow_less_equal_than<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using less_equal_than = less_equal_than_impl<T, U>;
template <typename T, typename U = T>
using less_equal_than_t = typename less_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool less_equal_than_v = less_equal_than<T, U>::value;

// greater_than
template <typename T, typename U = T, typename = void>
struct greater_than_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the greater than concept.");
};
template <typename T, typename U>
struct greater_than_impl<
  T, U, std::enable_if_t<std::disjunction_v<traits::is_greater_than<T, U>, traits::is_nothrow_greater_than<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using greater_than = greater_than_impl<T, U>;
template <typename T, typename U = T>
using greater_than_t = typename greater_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool greater_than_v = greater_than<T, U>::value;

// greater_equal_than
template <typename T, typename U = T, typename = void>
struct greater_equal_than_impl : std::false_type {
  static_assert(sizeof(T) == -1, "T fails to model the greater equal than concept.");
};
template <typename T, typename U>
struct greater_equal_than_impl<T, U,
                               std::enable_if_t<std::disjunction_v<traits::is_greater_equal_than<T, U>,
                                                                   traits::is_nothrow_greater_equal_than<T, U>>>>
  : std::true_type {
};
template <typename T, typename U = T>
using greater_equal_than = greater_equal_than_impl<T, U>;
template <typename T, typename U = T>
using greater_equal_than_t = typename greater_equal_than<T, U>::type;
template <typename T, typename U = T>
constexpr bool greater_equal_than_v = greater_equal_than<T, U>::value;


// other

// invocable
template <typename T, typename... Args>
struct Holder {
};
template <typename Holder, typename = void>
struct invocable_impl : std::false_type {
  static_assert(sizeof(Holder) == -1, "T fails to model the invocable concept.");
};
template <template <class T, class... Args> class Holder, typename T, typename... Args>
struct invocable_impl<
  Holder<T, Args...>,
  std::enable_if_t<std::disjunction_v<traits::is_invocable<T, Args...>, traits::is_nothrow_invocable<T, Args...>>>>
  : std::true_type {
};
template <typename T, typename... Args>
using invocable = invocable_impl<Holder<T, Args...>>;
template <typename T, typename... Args>
using invocable_t = typename invocable<T, Args...>::type;
template <typename T, typename... Args>
constexpr bool invocable_v = invocable<T, Args...>::value;

// invocable r
template <typename R, typename T, typename... Args>
struct HolderR {
};
template <typename Holder, typename = void>
struct invocable_r_impl : std::false_type {
  static_assert(sizeof(Holder) == -1, "T fails to model the invocable r concept.");
};
template <template <class R, class T, class... Args> class Holder, typename R, typename T, typename... Args>
struct invocable_r_impl<Holder<R, T, Args...>,
                        std::enable_if_t<std::disjunction_v<traits::is_invocable_r<R, T, Args...>,
                                                            traits::is_nothrow_invocable_r<R, T, Args...>>>>
  : std::true_type {
};
template <typename R, typename T, typename... Args>
using invocable_r = invocable_impl<Holder<R, T, Args...>>;
template <typename R, typename T, typename... Args>
using invocable_r_t = typename invocable_r<R, T, Args...>::type;
template <typename R, typename T, typename... Args>
constexpr bool invocable_r_v = invocable_r<R, T, Args...>::value;

}}} // namespace concepts::utility::details


#endif // CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
