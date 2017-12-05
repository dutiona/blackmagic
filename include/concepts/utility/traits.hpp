#pragma once

#ifndef CONCEPTS_UTILITY_TRAITS_HPP_
#define CONCEPTS_UTILITY_TRAITS_HPP_

#include "details/traits_impl.hpp"

#include <iterator>
#include <type_traits>

namespace traits { namespace utility {

// member access

// is_dereferenceable : *a
template <typename T>
using is_dereferenceable = details::is_dereferenceable_impl<T>;
template <typename T>
using is_dereferenceable_t = typename is_dereferenceable<T>::type;
template <typename T>
constexpr bool is_dereferenceable_v = is_dereferenceable<T>::value;

// is_address_of : &a
template <typename T>
using is_address_of = details::is_address_of_impl<T>;
template <typename T>
using is_address_of_t = typename is_address_of<T>::type;
template <typename T>
constexpr bool is_address_of_v = is_address_of<T>::value;

// is_subscript : a[b]
template <typename T, typename I>
using is_subscript = details::is_subscript_impl<T, I>;
template <typename T, typename I>
using is_subscript_t = typename is_subscript<T, I>::type;
template <typename T, typename I>
constexpr bool is_subscript_v = is_subscript<T, I>::value;


// assignement

template <typename T, typename U = T>
using assignable_t = decltype(std::declval<T>() = std::declval<U>()); // a = b

template <typename T, typename U = T>
using plus_assignable_t = decltype(std::declval<T>() += std::declval<U>()); // a += b

template <typename T, typename U = T>
using less_assignable_t = decltype(std::declval<T>() = std::declval<U>()); // a -= b

template <typename T, typename U = T>
using mult_assignable_t = decltype(std::declval<T>() *= std::declval<U>()); // a *= b

template <typename T, typename U = T>
using div_assignable_t = decltype(std::declval<T>() /= std::declval<U>()); // a /= b

template <typename T, typename U = T>
using mod_assignable_t = decltype(std::declval<T>() %= std::declval<U>()); // a %= b

template <typename T, typename U = T>
using and_assignable_t = decltype(std::declval<T>() &= std::declval<U>()); // a &= b

template <typename T, typename U = T>
using or_assignable_t = decltype(std::declval<T>() |= std::declval<U>()); // a |= b

template <typename T, typename U = T>
using xor_assignable_t = decltype(std::declval<T>() ^= std::declval<U>()); // a ^= b

template <typename T, typename U = T>
using lshift_assignable_t = decltype(std::declval<T>() <<= std::declval<U>()); // a <<= b

template <typename T, typename U = T>
using rshift_assignable_t = decltype(std::declval<T>() |= std::declval<U>()); // a >>= b


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