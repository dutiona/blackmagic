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
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct valid_impl<T, std::void_t<std::disjunction<traits::is_valid_t<T>, traits::is_nothrow_valid_t<T>>>>
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
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct dereferenceable_impl<
  T, std::void_t<std::disjunction<traits::is_dereferenceable_t<T>, traits::is_nothrow_dereferenceable_t<T>>>>
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
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct address_of_impl<T, std::void_t<std::disjunction<traits::is_address_of_t<T>, traits::is_nothrow_address_of_t<T>>>>
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
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename I>
struct subscript_impl<T, I,
                      std::void_t<std::disjunction<traits::is_subscript_t<T, I>, traits::is_nothrow_subscript_t<T, I>>>>
  : std::true_type {
};

template <typename T, typename I>
using subscript = subscript_impl<T, I>;
template <typename T, typename I>
using subscript_t = typename subscript<T, I>::type;
template <typename T, typename I>
constexpr bool subscript_v = subscript<T, I>::value;


// assignement

// is_assignable
template <typename T, typename U = T, typename = void>
struct is_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() = std::declval<U>())>> : std::true_type {
};
// is_nothrow_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() = std::declval<U>())>>
  : is_assignable_impl<T, U, Valid> {
};

// is_plus_assignable
template <typename T, typename U = T, typename = void>
struct is_plus_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_plus_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() += std::declval<U>())>> : std::true_type {
};
// is_nothrow_plus_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_plus_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_plus_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() += std::declval<U>())>>
  : is_plus_assignable_impl<T, U, Valid> {
};

// is_less_assignable
template <typename T, typename U = T, typename = void>
struct is_less_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_less_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() -= std::declval<U>())>> : std::true_type {
};
// is_nothrow_less_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() -= std::declval<U>())>>
  : is_less_assignable_impl<T, U, Valid> {
};

// is_mult_assignable
template <typename T, typename U = T, typename = void>
struct is_mult_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mult_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() *= std::declval<U>())>> : std::true_type {
};
// is_nothrow_mult_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mult_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mult_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() *= std::declval<U>())>>
  : is_mult_assignable_impl<T, U, Valid> {
};

// is_div_assignable
template <typename T, typename U = T, typename = void>
struct is_div_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_div_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() /= std::declval<U>())>> : std::true_type {
};
// is_nothrow_div_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_div_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_div_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() /= std::declval<U>())>>
  : is_div_assignable_impl<T, U, Valid> {
};

// is_mod_assignable
template <typename T, typename U = T, typename = void>
struct is_mod_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mod_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() %= std::declval<U>())>> : std::true_type {
};
// is_nothrow_mod_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mod_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mod_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() %= std::declval<U>())>>
  : is_mod_assignable_impl<T, U, Valid> {
};

// is_or_assignable
template <typename T, typename U = T, typename = void>
struct is_or_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_or_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() |= std::declval<U>())>> : std::true_type {
};
// is_nothrow_or_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_or_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_or_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() |= std::declval<U>())>>
  : is_or_assignable_impl<T, U, Valid> {
};

// is_and_assignable
template <typename T, typename U = T, typename = void>
struct is_and_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_and_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() &= std::declval<U>())>> : std::true_type {
};
// is_nothrow_and_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_and_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_and_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() &= std::declval<U>())>>
  : is_and_assignable_impl<T, U, Valid> {
};

// is_xor_assignable
template <typename T, typename U = T, typename = void>
struct is_xor_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_xor_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() ^= std::declval<U>())>> : std::true_type {
};
// is_nothrow_xor_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_xor_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_xor_assignable_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() ^= std::declval<U>())>>
  : is_xor_assignable_impl<T, U, Valid> {
};

// is_lshift_assignable
template <typename T, typename U = T, typename = void>
struct is_lshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_lshift_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() <<= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_lshift_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_lshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_lshift_assignable_impl<T, U, Valid,
                                         std::enable_if_t<noexcept(std::declval<T>() <<= std::declval<U>())>>
  : is_lshift_assignable_impl<T, U, Valid> {
};

// is_rshift_assignable
template <typename T, typename U = T, typename = void>
struct is_rshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_rshift_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() >>= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_rshift_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_rshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_rshift_assignable_impl<T, U, Valid,
                                         std::enable_if_t<noexcept(std::declval<T>() >>= std::declval<U>())>>
  : is_rshift_assignable_impl<T, U, Valid> {
};


// arithmetic

// is_positive
template <typename T, typename = void>
struct is_positive_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_positive_impl<T, std::void_t<decltype(+std::declval<T>())>> : std::true_type {
};
// is_nothrow_positive
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_positive_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_positive_impl<T, Valid, std::enable_if_t<noexcept(+std::declval<T>())>> : is_positive_impl<T, Valid> {
};

// is_negative
template <typename T, typename = void>
struct is_negative_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_negative_impl<T, std::void_t<decltype(-std::declval<T>())>> : std::true_type {
};
// is_nothrow_negative
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_negative_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_negative_impl<T, Valid, std::enable_if_t<noexcept(-std::declval<T>())>> : is_negative_impl<T, Valid> {
};

// is_not
template <typename T, typename = void>
struct is_not_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_not_impl<T, std::void_t<decltype(~std::declval<T>())>> : std::true_type {
};
// is_nothrow_not
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_not_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_not_impl<T, Valid, std::enable_if_t<noexcept(~std::declval<T>())>> : is_not_impl<T, Valid> {
};

// is_plus
template <typename T, typename U = T, typename = void>
struct is_plus_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_plus_impl<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type {
};
// is_nothrow_plus
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_plus_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_plus_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() + std::declval<U>())>>
  : is_plus_impl<T, U, Valid> {
};

// is_less
template <typename T, typename U = T, typename = void>
struct is_less_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_less_impl<T, U, std::void_t<decltype(std::declval<T>() - std::declval<U>())>> : std::true_type {
};
// is_nothrow_less
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() - std::declval<U>())>>
  : is_less_impl<T, U, Valid> {
};

// is_mult
template <typename T, typename U = T, typename = void>
struct is_mult_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mult_impl<T, U, std::void_t<decltype(std::declval<T>() * std::declval<U>())>> : std::true_type {
};
// is_nothrow_mult
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mult_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mult_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() * std::declval<U>())>>
  : is_mult_impl<T, U, Valid> {
};

// is_div
template <typename T, typename U = T, typename = void>
struct is_div_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_div_impl<T, U, std::void_t<decltype(std::declval<T>() / std::declval<U>())>> : std::true_type {
};
// is_nothrow_div
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_div_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_div_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() / std::declval<U>())>>
  : is_div_impl<T, U, Valid> {
};

// is_mod
template <typename T, typename U = T, typename = void>
struct is_mod_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mod_impl<T, U, std::void_t<decltype(std::declval<T>() % std::declval<U>())>> : std::true_type {
};
// is_nothrow_mod
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mod_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mod_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() % std::declval<U>())>>
  : is_mod_impl<T, U, Valid> {
};

// is_and
template <typename T, typename U = T, typename = void>
struct is_and_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_and_impl<T, U, std::void_t<decltype(std::declval<T>() & std::declval<U>())>> : std::true_type {
};
// is_nothrow_and
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_and_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_and_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() & std::declval<U>())>>
  : is_and_impl<T, U, Valid> {
};

// is_or
template <typename T, typename U = T, typename = void>
struct is_or_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_or_impl<T, U, std::void_t<decltype(std::declval<T>() | std::declval<U>())>> : std::true_type {
};
// is_nothrow_or
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_or_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_or_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() | std::declval<U>())>>
  : is_or_impl<T, U, Valid> {
};

// is_xor
template <typename T, typename U = T, typename = void>
struct is_xor_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_xor_impl<T, U, std::void_t<decltype(std::declval<T>() ^ std::declval<U>())>> : std::true_type {
};
// is_nothrow_or
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_xor_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_xor_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() ^ std::declval<U>())>>
  : is_xor_impl<T, U, Valid> {
};

// is_lshift
template <typename T, typename U = T, typename = void>
struct is_lshift_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_lshift_impl<T, U, std::void_t<decltype(std::declval<T>() << std::declval<U>())>> : std::true_type {
};
// is_nothrow_lshift
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_lshift_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_lshift_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() << std::declval<U>())>>
  : is_lshift_impl<T, U, Valid> {
};

// is_rshift
template <typename T, typename U = T, typename = void>
struct is_rshift_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_rshift_impl<T, U, std::void_t<decltype(std::declval<T>() << std::declval<U>())>> : std::true_type {
};
// is_nothrow_rshift
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_rshift_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_rshift_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() >> std::declval<U>())>>
  : is_rshift_impl<T, U, Valid> {
};


// increment / decrement

// is_pre_incrementable
template <typename T, typename = void>
struct is_pre_incrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_pre_incrementable_impl<T, std::void_t<decltype(++std::declval<T>())>> : std::true_type {
};
// is_nothrow_pre_incrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_pre_incrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_pre_incrementable_impl<T, Valid, std::enable_if_t<noexcept(++std::declval<T>())>>
  : is_pre_incrementable_impl<T, Valid> {
};

// is_post_incrementable
template <typename T, typename = void>
struct is_post_incrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_post_incrementable_impl<T, std::void_t<decltype(std::declval<T>()++)>> : std::true_type {
};
// is_nothrow_post_incrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_post_incrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_post_incrementable_impl<T, Valid, std::enable_if_t<noexcept(std::declval<T>()++)>>
  : is_post_incrementable_impl<T, Valid> {
};

// is_pre_decrementable
template <typename T, typename = void>
struct is_pre_decrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_pre_decrementable_impl<T, std::void_t<decltype(--std::declval<T>())>> : std::true_type {
};
// is_nothrow_pre_decrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_pre_decrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_pre_decrementable_impl<T, Valid, std::enable_if_t<noexcept(--std::declval<T>())>>
  : is_pre_decrementable_impl<T, Valid> {
};

// is_post_decrementable
template <typename T, typename = void>
struct is_post_decrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_post_decrementable_impl<T, std::void_t<decltype(std::declval<T>()--)>> : std::true_type {
};
// is_nothrow_post_decrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_post_decrementable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_post_decrementable_impl<T, Valid, std::enable_if_t<noexcept(std::declval<T>()--)>>
  : is_post_decrementable_impl<T, Valid> {
};


// comparison

// is_equality
template <typename T, typename U = T, typename = void>
struct is_equality_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_equality_impl<T, U, std::void_t<decltype(std::declval<T>() == std::declval<U>())>> : std::true_type {
};
// is_nothrow_equality
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_equality_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_equality_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() == std::declval<U>())>>
  : is_equality_impl<T, U, Valid> {
};

// is_inequality
template <typename T, typename U = T, typename = void>
struct is_inequality_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_inequality_impl<T, U, std::void_t<decltype(std::declval<T>() != std::declval<U>())>> : std::true_type {
};
// is_nothrow_inequality
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_inequality_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_inequality_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() != std::declval<U>())>>
  : is_inequality_impl<T, U, Valid> {
};

// is_less_than
template <typename T, typename U = T, typename = void>
struct is_less_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_less_than_impl<T, U, std::void_t<decltype(std::declval<T>() < std::declval<U>())>> : std::true_type {
};
// is_nothrow_less_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() < std::declval<U>())>>
  : is_less_than_impl<T, U, Valid> {
};

// is_less_equal_than
template <typename T, typename U = T, typename = void>
struct is_less_equal_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_less_equal_than_impl<T, U, std::void_t<decltype(std::declval<T>() <= std::declval<U>())>> : std::true_type {
};
// is_nothrow_less_equal_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_equal_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_equal_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() <= std::declval<U>())>>
  : is_less_equal_than_impl<T, U, Valid> {
};

// is_greater_than
template <typename T, typename U = T, typename = void>
struct is_greater_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_greater_than_impl<T, U, std::void_t<decltype(std::declval<T>() > std::declval<U>())>> : std::true_type {
};
// is_nothrow_greater_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_greater_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_greater_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() > std::declval<U>())>>
  : is_greater_than_impl<T, U, Valid> {
};

// is_greater_equal_than
template <typename T, typename U = T, typename = void>
struct is_greater_equal_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_greater_equal_than_impl<T, U, std::void_t<decltype(std::declval<T>() >= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_greater_equal_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_greater_equal_than_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U, typename Valid>
struct is_nothrow_greater_equal_than_impl<T, U, Valid,
                                          std::enable_if_t<noexcept(std::declval<T>() >= std::declval<U>())>>
  : is_greater_equal_than_impl<T, U, Valid> {
};


// other

// is_function_call
template <typename T, typename = void, typename... Args>
struct is_function_call_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename... Args>
struct is_function_call_impl<T, std::void_t<decltype(std::declval<T>()(std::declval<Args>()...))>, Args...>
  : std::true_type {
};
// is_nothrow_function_call
template <typename T, typename Valid = void, typename = void, typename... Args>
struct is_nothrow_function_call_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid, typename... Args>
struct is_nothrow_function_call_impl<T, Valid, std::enable_if_t<noexcept(std::declval<T>()(std::declval<Args>()...))>,
                                     Args...> : is_function_call_impl<T, Valid, Args...> {
};

}}} // namespace concepts::utility::details


#endif // CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
