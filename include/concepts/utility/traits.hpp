#pragma once

#ifndef CONCEPTS_UTILITY_TRAITS_HPP_
#define CONCEPTS_UTILITY_TRAITS_HPP_

#include "details/traits_impl.hpp"

#include <type_traits>

namespace traits { namespace utility {

// validity

// is_valid
template <typename T>
using is_valid = details::is_valid_impl<T>;
template <typename T>
using is_valid_t = typename is_valid<T>::type;
template <typename T>
constexpr bool is_valid_v = is_valid<T>::value;
// is_nothrow_valid
template <typename T>
using is_nothrow_valid = details::is_nothrow_valid_impl<T>;
template <typename T>
using is_nothrow_valid_t = typename is_nothrow_valid<T>::type;
template <typename T>
constexpr bool is_nothrow_valid_v = is_nothrow_valid<T>::value;

// member access

// is_dereferenceable : *a
template <typename T>
using is_dereferenceable = details::is_dereferenceable_impl<T>;
template <typename T>
using is_dereferenceable_t = typename is_dereferenceable<T>::type;
template <typename T>
constexpr bool is_dereferenceable_v = is_dereferenceable<T>::value;
// is_nothrow_dereferenceable
template <typename T>
using is_nothrow_dereferenceable = details::is_nothrow_dereferenceable_impl<T>;
template <typename T>
using is_nothrow_dereferenceable_t = typename is_nothrow_dereferenceable<T>::type;
template <typename T>
constexpr bool is_nothrow_dereferenceable_v = is_nothrow_dereferenceable<T>::value;

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


// TODO
// arithmetic

template <typename T>
using positive_t = decltype(+std::declval<T>()); // +a

template <typename T>
using negative_t = decltype(-std::declval<T>()); // -a

template <typename T>
using not_t = decltype(~std::declval<T>()); // ~a

template <typename T, typename U = T>
using plus_t = decltype(std::declval<T>() + std::declval<U>()); // a + b

template <typename T, typename U = T>
using less_t = decltype(std::declval<T>() - std::declval<U>()); // a - b

template <typename T, typename U = T>
using mult_t = decltype(std::declval<T>() * std::declval<U>()); // a * b

template <typename T, typename U = T>
using div_t = decltype(std::declval<T>() / std::declval<U>()); // a / b

template <typename T, typename U = T>
using mod_t = decltype(std::declval<T>() % std::declval<U>()); // a % b

template <typename T, typename U = T>
using and_t = decltype(std::declval<T>() & std::declval<U>()); // a & b

template <typename T, typename U = T>
using or_t = decltype(std::declval<T>() | std::declval<U>()); // a | b

template <typename T, typename U = T>
using xor_t = decltype(std::declval<T>() ^ std::declval<U>()); // a ^ b

template <typename T, typename U = T>
using lshift_t = decltype(std::declval<T>() << std::declval<U>()); // a << b

template <typename T, typename U = T>
using rshift_t = decltype(std::declval<T>() >> std::declval<U>()); // a >> b


// increment / decrement

template <typename T>
using pre_incrementable_t = decltype(++std::declval<T>()); // ++a

template <typename T>
using post_incrementable_t = decltype(std::declval<T>()++); // a++

template <typename T>
using pre_decrementable_t = decltype(--std::declval<T>()); // --a

template <typename T>
using post_decrementable_t = decltype(std::declval<T>()--); // a--


// comparison

template <typename T, typename U = T>
using equality_t = decltype(std::declval<T>() == std::declval<U>()); // a == b

template <typename T, typename U = T>
using inequality_t = decltype(std::declval<T>() != std::declval<U>()); // a != b

template <typename T, typename U = T>
using less_than_t = decltype(std::declval<T>() < std::declval<U>()); // a < b

template <typename T, typename U = T>
using less_equal_than_t = decltype(std::declval<T>() <= std::declval<U>()); // a <= b

template <typename T, typename U = T>
using greater_than_t = decltype(std::declval<T>() > std::declval<U>()); // a > b

template <typename T, typename U = T>
using greater_equal_than_t = decltype(std::declval<T>() >= std::declval<U>()); // a >= b


// other

template <typename T, typename... Args>
using function_call_t = decltype(std::declval<T>()(std::declval<Args>()...)); // a(args...)

}} // namespace traits::utility


#endif // CONCEPTS_TRAITS_UTILIY_HPP_