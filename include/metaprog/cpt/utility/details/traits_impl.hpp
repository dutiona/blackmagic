#pragma once

#ifndef METAPROG_CPT_UTILIY_DETAILS_TRAITS_IMPL_HPP_
#define METAPROG_CPT_UTILIY_DETAILS_TRAITS_IMPL_HPP_

#ifndef _MSC_VER
#include "../../../common/common.hpp"
#endif

#include <type_traits>

namespace cpt::traits::utility::details {

// member access

// is_indirection
template <typename T, typename = void>
struct is_indirection_impl : std::false_type {
};
template <typename T>
struct is_indirection_impl<T, std::void_t<decltype(*std::declval<T>())>> : std::true_type {
};
// is_nothrow_indirection
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_indirection_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_indirection_impl<T, Valid, std::enable_if_t<noexcept(*std::declval<T>())>>
  : is_indirection_impl<T, Valid> {
};

// is_address_of
template <typename T, typename = void>
struct is_address_of_impl : std::false_type {
};
template <typename T>
struct is_address_of_impl<T, std::void_t<decltype(&std::declval<T>())>> : std::true_type {
};
// is_nothrow_dereferenceable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_address_of_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_address_of_impl<T, Valid, std::enable_if_t<noexcept(&std::declval<T>())>>
  : is_address_of_impl<T, Valid> {
};

// is_subscript
template <typename T, typename I, typename = void>
struct is_subscript_impl : std::false_type {
};
template <typename T, typename I>
struct is_subscript_impl<T, I, std::void_t<decltype(std::declval<T>()[std::declval<I>()])>> : std::true_type {
};
// is_nothrow_subscript
template <typename T, typename I, typename Valid = void, typename = void>
struct is_nothrow_subscript_impl : std::false_type {
};
template <typename T, typename I, typename Valid>
struct is_nothrow_subscript_impl<T, I, Valid, std::enable_if_t<noexcept(std::declval<T>()[std::declval<I>()])>>
  : is_subscript_impl<T, I, Valid> {
};

// is_pointer_to_member_of_object
template <typename T, typename I, typename = void>
struct is_pointer_to_member_of_object_impl : std::false_type {
};
template <typename T, typename I>
struct is_pointer_to_member_of_object_impl<T, I, std::void_t<decltype(std::declval<T>().*std::declval<I>())>>
  : std::true_type {
};
// is_nothrow_pointer_to_member_of_object
template <typename T, typename I, typename Valid = void, typename = void>
struct is_nothrow_pointer_to_member_of_object_impl : std::false_type {
};
template <typename T, typename I, typename Valid>
struct is_nothrow_pointer_to_member_of_object_impl<T, I, Valid,
                                                   std::enable_if_t<noexcept(std::declval<T>().*std::declval<I>())>>
  : is_pointer_to_member_of_object_impl<T, I, Valid> {
};

// is_pointer_to_member_of_pointer
template <typename T, typename I, typename = void>
struct is_pointer_to_member_of_pointer_impl : std::false_type {
};
template <typename T, typename I>
struct is_pointer_to_member_of_pointer_impl<T, I, std::void_t<decltype(std::declval<T>()->*std::declval<I>())>>
  : std::true_type {
};
// is_nothrow_pointer_to_member_of_pointer
template <typename T, typename I, typename Valid = void, typename = void>
struct is_nothrow_pointer_to_member_of_pointer_impl : std::false_type {
};
template <typename T, typename I, typename Valid>
struct is_nothrow_pointer_to_member_of_pointer_impl<T, I, Valid,
                                                    std::enable_if_t<noexcept(std::declval<T>()->*std::declval<I>())>>
  : is_pointer_to_member_of_pointer_impl<T, I, Valid> {
};


// assignement

// is_assignable
template <typename T, typename U = T, typename = void>
struct is_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_assignable_impl<T, U, std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() = std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() = std::declval<U>())>>
  : is_assignable_impl<T, U, Valid> {
};

// is_plus_assignable
template <typename T, typename U = T, typename = void>
struct is_plus_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_plus_assignable_impl<T, U,
                               std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() += std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_plus_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_plus_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_plus_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() += std::declval<U>())>>
  : is_plus_assignable_impl<T, U, Valid> {
};

// is_less_assignable
template <typename T, typename U = T, typename = void>
struct is_less_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_less_assignable_impl<T, U,
                               std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() -= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_less_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() -= std::declval<U>())>>
  : is_less_assignable_impl<T, U, Valid> {
};

// is_mult_assignable
template <typename T, typename U = T, typename = void>
struct is_mult_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_mult_assignable_impl<T, U,
                               std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() *= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_mult_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mult_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mult_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() *= std::declval<U>())>>
  : is_mult_assignable_impl<T, U, Valid> {
};

// is_div_assignable
template <typename T, typename U = T, typename = void>
struct is_div_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_div_assignable_impl<T, U,
                              std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() /= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_div_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_div_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_div_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() /= std::declval<U>())>>
  : is_div_assignable_impl<T, U, Valid> {
};

// is_mod_assignable
template <typename T, typename U = T, typename = void>
struct is_mod_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_mod_assignable_impl<T, U,
                              std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() %= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_mod_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mod_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mod_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() %= std::declval<U>())>>
  : is_mod_assignable_impl<T, U, Valid> {
};

// is_or_assignable
template <typename T, typename U = T, typename = void>
struct is_or_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_or_assignable_impl<T, U,
                             std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() |= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_or_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_or_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_or_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() |= std::declval<U>())>>
  : is_or_assignable_impl<T, U, Valid> {
};

// is_and_assignable
template <typename T, typename U = T, typename = void>
struct is_and_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_and_assignable_impl<T, U,
                              std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() &= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_and_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_and_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_and_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() &= std::declval<U>())>>
  : is_and_assignable_impl<T, U, Valid> {
};

// is_xor_assignable
template <typename T, typename U = T, typename = void>
struct is_xor_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_xor_assignable_impl<T, U,
                              std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() ^= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_xor_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_xor_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_xor_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() ^= std::declval<U>())>>
  : is_xor_assignable_impl<T, U, Valid> {
};

// is_lshift_assignable
template <typename T, typename U = T, typename = void>
struct is_lshift_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_lshift_assignable_impl<
  T, U, std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() <<= std::declval<U>())>> : std::true_type {
};
// is_nothrow_lshift_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_lshift_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_lshift_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() <<= std::declval<U>())>>
  : is_lshift_assignable_impl<T, U, Valid> {
};

// is_rshift_assignable
template <typename T, typename U = T, typename = void>
struct is_rshift_assignable_impl : std::false_type {
};
template <typename T, typename U>
struct is_rshift_assignable_impl<
  T, U, std::void_t<decltype(std::declval<std::remove_reference_t<T>&>() >>= std::declval<U>())>> : std::true_type {
};
// is_nothrow_rshift_assignable
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_rshift_assignable_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_rshift_assignable_impl<
  T, U, Valid, std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>() >>= std::declval<U>())>>
  : is_rshift_assignable_impl<T, U, Valid> {
};


// arithmetic

// is_positive
template <typename T, typename = void>
struct is_positive_impl : std::false_type {
};
template <typename T>
struct is_positive_impl<T, std::void_t<decltype(+std::declval<T>())>> : std::true_type {
};
// is_nothrow_positive
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_positive_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_positive_impl<T, Valid, std::enable_if_t<noexcept(+std::declval<T>())>> : is_positive_impl<T, Valid> {
};

// is_negative
template <typename T, typename = void>
struct is_negative_impl : std::false_type {
};
template <typename T>
struct is_negative_impl<T, std::void_t<decltype(-std::declval<T>())>> : std::true_type {
};
// is_nothrow_negative
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_negative_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_negative_impl<T, Valid, std::enable_if_t<noexcept(-std::declval<T>())>> : is_negative_impl<T, Valid> {
};

// is_not
template <typename T, typename = void>
struct is_not_impl : std::false_type {
};
template <typename T>
struct is_not_impl<T, std::void_t<decltype(~std::declval<T>())>> : std::true_type {
};
// is_nothrow_not
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_not_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_not_impl<T, Valid, std::enable_if_t<noexcept(~std::declval<T>())>> : is_not_impl<T, Valid> {
};

// is_plus
template <typename T, typename U = T, typename = void>
struct is_plus_impl : std::false_type {
};
template <typename T, typename U>
struct is_plus_impl<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type {
};
// is_nothrow_plus
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_plus_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_plus_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() + std::declval<U>())>>
  : is_plus_impl<T, U, Valid> {
};

// is_less
template <typename T, typename U = T, typename = void>
struct is_less_impl : std::false_type {
};
template <typename T, typename U>
struct is_less_impl<T, U, std::void_t<decltype(std::declval<T>() - std::declval<U>())>> : std::true_type {
};
// is_nothrow_less
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() - std::declval<U>())>>
  : is_less_impl<T, U, Valid> {
};

// is_mult
template <typename T, typename U = T, typename = void>
struct is_mult_impl : std::false_type {
};
template <typename T, typename U>
struct is_mult_impl<T, U, std::void_t<decltype(std::declval<T>() * std::declval<U>())>> : std::true_type {
};
// is_nothrow_mult
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mult_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mult_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() * std::declval<U>())>>
  : is_mult_impl<T, U, Valid> {
};

// is_div
template <typename T, typename U = T, typename = void>
struct is_div_impl : std::false_type {
};
template <typename T, typename U>
struct is_div_impl<T, U, std::void_t<decltype(std::declval<T>() / std::declval<U>())>> : std::true_type {
};
// is_nothrow_div
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_div_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_div_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() / std::declval<U>())>>
  : is_div_impl<T, U, Valid> {
};

// is_mod
template <typename T, typename U = T, typename = void>
struct is_mod_impl : std::false_type {
};
template <typename T, typename U>
struct is_mod_impl<T, U, std::void_t<decltype(std::declval<T>() % std::declval<U>())>> : std::true_type {
};
// is_nothrow_mod
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_mod_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_mod_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() % std::declval<U>())>>
  : is_mod_impl<T, U, Valid> {
};

// is_and
template <typename T, typename U = T, typename = void>
struct is_and_impl : std::false_type {
};
template <typename T, typename U>
struct is_and_impl<T, U, std::void_t<decltype(std::declval<T>() & std::declval<U>())>> : std::true_type {
};
// is_nothrow_and
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_and_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_and_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() & std::declval<U>())>>
  : is_and_impl<T, U, Valid> {
};

// is_or
template <typename T, typename U = T, typename = void>
struct is_or_impl : std::false_type {
};
template <typename T, typename U>
struct is_or_impl<T, U, std::void_t<decltype(std::declval<T>() | std::declval<U>())>> : std::true_type {
};
// is_nothrow_or
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_or_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_or_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() | std::declval<U>())>>
  : is_or_impl<T, U, Valid> {
};

// is_xor
template <typename T, typename U = T, typename = void>
struct is_xor_impl : std::false_type {
};
template <typename T, typename U>
struct is_xor_impl<T, U, std::void_t<decltype(std::declval<T>() ^ std::declval<U>())>> : std::true_type {
};
// is_nothrow_or
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_xor_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_xor_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() ^ std::declval<U>())>>
  : is_xor_impl<T, U, Valid> {
};

// is_lshift
template <typename T, typename U = T, typename = void>
struct is_lshift_impl : std::false_type {
};
template <typename T, typename U>
struct is_lshift_impl<T, U, std::void_t<decltype(std::declval<T>() << std::declval<U>())>> : std::true_type {
};
// is_nothrow_lshift
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_lshift_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_lshift_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() << std::declval<U>())>>
  : is_lshift_impl<T, U, Valid> {
};

// is_rshift
template <typename T, typename U = T, typename = void>
struct is_rshift_impl : std::false_type {
};
template <typename T, typename U>
struct is_rshift_impl<T, U, std::void_t<decltype(std::declval<T>() >> std::declval<U>())>> : std::true_type {
};
// is_nothrow_rshift
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_rshift_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_rshift_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() >> std::declval<U>())>>
  : is_rshift_impl<T, U, Valid> {
};


// increment / decrement

// is_pre_incrementable
template <typename T, typename = void>
struct is_pre_incrementable_impl : std::false_type {
};
template <typename T>
struct is_pre_incrementable_impl<T, std::void_t<decltype(++std::declval<std::remove_reference_t<T>&>())>>
  : std::true_type {
};
// is_nothrow_pre_incrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_pre_incrementable_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_pre_incrementable_impl<T, Valid,
                                         std::enable_if_t<noexcept(++std::declval<std::remove_reference_t<T>&>())>>
  : is_pre_incrementable_impl<T, Valid> {
};

// is_post_incrementable
template <typename T, typename = void>
struct is_post_incrementable_impl : std::false_type {
};
template <typename T>
struct is_post_incrementable_impl<T, std::void_t<decltype(std::declval<std::remove_reference_t<T>&>()++)>>
  : std::true_type {
};
// is_nothrow_post_incrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_post_incrementable_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_post_incrementable_impl<T, Valid,
                                          std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>()++)>>
  : is_post_incrementable_impl<T, Valid> {
};

// is_pre_decrementable
template <typename T, typename = void>
struct is_pre_decrementable_impl : std::false_type {
};
template <typename T>
struct is_pre_decrementable_impl<T, std::void_t<decltype(--std::declval<std::remove_reference_t<T>&>())>>
  : std::true_type {
};
// is_nothrow_pre_decrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_pre_decrementable_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_pre_decrementable_impl<T, Valid,
                                         std::enable_if_t<noexcept(--std::declval<std::remove_reference_t<T>&>())>>
  : is_pre_decrementable_impl<T, Valid> {
};

// is_post_decrementable
template <typename T, typename = void>
struct is_post_decrementable_impl : std::false_type {
};
template <typename T>
struct is_post_decrementable_impl<T, std::void_t<decltype(std::declval<std::remove_reference_t<T>&>()--)>>
  : std::true_type {
};
// is_nothrow_post_decrementable
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_post_decrementable_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_post_decrementable_impl<T, Valid,
                                          std::enable_if_t<noexcept(std::declval<std::remove_reference_t<T>&>()--)>>
  : is_post_decrementable_impl<T, Valid> {
};


// comparison

// is_equality
template <typename T, typename U = T, typename = void>
struct is_equality_impl : std::false_type {
};
template <typename T, typename U>
struct is_equality_impl<T, U, std::void_t<decltype(std::declval<T>() == std::declval<U>())>> : std::true_type {
};
// is_nothrow_equality
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_equality_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_equality_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() == std::declval<U>())>>
  : is_equality_impl<T, U, Valid> {
};

// is_inequality
template <typename T, typename U = T, typename = void>
struct is_inequality_impl : std::false_type {
};
template <typename T, typename U>
struct is_inequality_impl<T, U, std::void_t<decltype(std::declval<T>() != std::declval<U>())>> : std::true_type {
};
// is_nothrow_inequality
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_inequality_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_inequality_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() != std::declval<U>())>>
  : is_inequality_impl<T, U, Valid> {
};

// is_less_than
template <typename T, typename U = T, typename = void>
struct is_less_than_impl : std::false_type {
};
template <typename T, typename U>
struct is_less_than_impl<T, U, std::void_t<decltype(std::declval<T>() < std::declval<U>())>> : std::true_type {
};
// is_nothrow_less_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_than_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() < std::declval<U>())>>
  : is_less_than_impl<T, U, Valid> {
};

// is_less_equal_than
template <typename T, typename U = T, typename = void>
struct is_less_equal_than_impl : std::false_type {
};
template <typename T, typename U>
struct is_less_equal_than_impl<T, U, std::void_t<decltype(std::declval<T>() <= std::declval<U>())>> : std::true_type {
};
// is_nothrow_less_equal_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_less_equal_than_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_less_equal_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() <= std::declval<U>())>>
  : is_less_equal_than_impl<T, U, Valid> {
};

// is_greater_than
template <typename T, typename U = T, typename = void>
struct is_greater_than_impl : std::false_type {
};
template <typename T, typename U>
struct is_greater_than_impl<T, U, std::void_t<decltype(std::declval<T>() > std::declval<U>())>> : std::true_type {
};
// is_nothrow_greater_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_greater_than_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_greater_than_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() > std::declval<U>())>>
  : is_greater_than_impl<T, U, Valid> {
};

// is_greater_equal_than
template <typename T, typename U = T, typename = void>
struct is_greater_equal_than_impl : std::false_type {
};
template <typename T, typename U>
struct is_greater_equal_than_impl<T, U, std::void_t<decltype(std::declval<T>() >= std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_greater_equal_than
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_greater_equal_than_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_greater_equal_than_impl<T, U, Valid,
                                          std::enable_if_t<noexcept(std::declval<T>() >= std::declval<U>())>>
  : is_greater_equal_than_impl<T, U, Valid> {
};


// is_logical_not
template <typename T, typename = void>
struct is_logical_not_impl : std::false_type {
};
template <typename T>
struct is_logical_not_impl<T, std::void_t<decltype(!std::declval<T>())>> : std::true_type {
};
// is_nothrow_logical_not
template <typename T, typename Valid = void, typename = void>
struct is_nothrow_logical_not_impl : std::false_type {
};
template <typename T, typename Valid>
struct is_nothrow_logical_not_impl<T, Valid, std::enable_if_t<noexcept(!std::declval<T>())>>
  : is_logical_not_impl<T, Valid> {
};

// is_logical_and
template <typename T, typename U = T, typename = void>
struct is_logical_and_impl : std::false_type {
};
template <typename T, typename U>
struct is_logical_and_impl<T, U, std::void_t<decltype(std::declval<T>() && std::declval<U>())>> : std::true_type {
};
// is_nothrow_logical_and
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_logical_and_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_logical_and_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() && std::declval<U>())>>
  : is_logical_and_impl<T, U, Valid> {
};

// is_logical_or
template <typename T, typename U = T, typename = void>
struct is_logical_or_impl : std::false_type {
};
template <typename T, typename U>
struct is_logical_or_impl<T, U, std::void_t<decltype(std::declval<T>() || std::declval<U>())>> : std::true_type {
};
// is_nothrow_logical_or
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_logical_or_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_logical_or_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>() || std::declval<U>())>>
  : is_logical_or_impl<T, U, Valid> {
};


// other

// is_comma
template <typename T, typename U = T, typename = void>
struct is_comma_impl : std::false_type {
};
template <typename T, typename U>
struct is_comma_impl<T, U, std::void_t<decltype(std::declval<T>(), std::declval<U>())>> : std::true_type {
};
// is_nothrow_comma
template <typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_comma_impl : std::false_type {
};
template <typename T, typename U, typename Valid>
struct is_nothrow_comma_impl<T, U, Valid, std::enable_if_t<noexcept(std::declval<T>(), std::declval<U>())>>
  : is_comma_impl<T, U, Valid> {
};

// is_ternary
template <typename B, typename T, typename U = T, typename = void>
struct is_ternary_impl : std::false_type {
};
template <typename B, typename T, typename U>
struct is_ternary_impl<B, T, U, std::void_t<decltype(std::declval<B>() ? std::declval<T>() : std::declval<U>())>>
  : std::true_type {
};
// is_nothrow_ternary
template <typename B, typename T, typename U = T, typename Valid = void, typename = void>
struct is_nothrow_ternary_impl : std::false_type {
};
template <typename B, typename T, typename U, typename Valid>
struct is_nothrow_ternary_impl<B, T, U, Valid,
                               std::enable_if_t<noexcept(std::declval<B>() ? std::declval<T>() : std::declval<U>())>>
  : is_ternary_impl<B, T, U, Valid> {
};

// is_invocable
template <typename T, typename... Args>
struct _holder {
};
#ifdef _MSC_VER
template <typename Holder, typename = void>
struct is_invocable_impl : std::false_type {
};
template <template <typename F, typename... Args> class Holder, typename F, typename... Args>
struct is_invocable_impl<Holder<F, Args...>> : std::is_invocable<F, Args...> {
};
#else
template <typename Holder, typename = void>
struct is_invocable_impl : std::false_type {
};
template <template <typename F, typename... Args> class Holder, typename F, typename... Args>
struct is_invocable_impl<Holder<F, Args...>,
                         std::void_t<decltype(std::invoke(std::declval<F>(), std::declval<Args>()...))>>
  : std::true_type {
};
#endif

// is_nothrow_invocable
#ifdef _MSC_VER
template <typename Holder, typename = void>
struct is_nothrow_invocable_impl : std::false_type {
};
template <template <typename F, typename... Args> class Holder, typename F, typename... Args>
struct is_nothrow_invocable_impl<Holder<F, Args...>> : std::is_nothrow_invocable<F, Args...> {
};
#else
template <typename Holder, typename Valid = void, typename = void>
struct is_nothrow_invocable_impl : std::false_type {
};
template <template <typename F, typename... Args> class Holder, typename Valid, typename F, typename... Args>
struct is_nothrow_invocable_impl<Holder<F, Args...>, Valid,
                                 std::enable_if_t<noexcept(std::invoke(std::declval<F>(), std::declval<Args>()...))>>
  : is_invocable_impl<_holder<F, Args...>, Valid> {
};
#endif


// is_invocable_r
template <typename R, typename F, typename... Args>
struct _holder_r {
};
#ifdef _MSC_VER
template <typename Holder, typename = void>
struct is_invocable_r_impl : std::false_type {
};
template <template <typename R, typename F, typename... Args> class Holder, typename R, typename F, typename... Args>
struct is_invocable_r_impl<Holder<R, F, Args...>> : std::is_invocable_r<R, F, Args...> {
};
#else
template <typename Holder, typename Valid = void, typename = void>
struct is_invocable_r_impl : std::false_type {
};
template <template <typename R, typename F, typename... Args> class Holder, typename Valid, typename R, typename F,
          typename... Args>
struct is_invocable_r_impl<Holder<R, F, Args...>, Valid,
                           std::enable_if_t<std::is_convertible_v<R, common::invoke_result_t<F, Args...>>>>
  : is_invocable_impl<_holder<F, Args...>, Valid> {
};
#endif

// is_nothrow_invocable_r
#ifdef _MSC_VER
template <typename Holder, typename = void>
struct is_nothrow_invocable_r_impl : std::false_type {
};
template <template <typename R, typename F, typename... Args> class Holder, typename R, typename F, typename... Args>
struct is_nothrow_invocable_r_impl<Holder<R, F, Args...>> : std::is_nothrow_invocable_r<R, F, Args...> {
};
#else
template <typename Holder, typename Valid = void, typename = void>
struct is_nothrow_invocable_r_impl : std::false_type {
};
template <template <typename R, typename F, typename... Args> class Holder, typename Valid, typename R, typename F,
          typename... Args>
struct is_nothrow_invocable_r_impl<Holder<R, F, Args...>, Valid,
                                   std::enable_if_t<std::is_convertible_v<R, common::invoke_result_t<F, Args...>>>>
  : is_nothrow_invocable_impl<_holder<F, Args...>, Valid> {
};
#endif

} // namespace cpt::traits::utility::details


#endif // METAPROG_CPT_UTILIY_DETAILS_TRAITS_IMPL_HPP_
