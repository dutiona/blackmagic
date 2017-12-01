#pragma once

#ifndef CPP14CONCEPTS_DETAILS_UTILIY_HPP_
#  define CPP14CONCEPTS_DETAILS_UTILIY_HPP_

#  include <iterator>
#  include <type_traits>

namespace cpp14concepts { namespace details {

// member access

template <typename T>
using dereferenceable_t = decltype(*std::declval<T>()); // *a

template <typename T>
using address_of_t = decltype(&std::declval<T>()); // &a

template <typename T, typename I>
using subscript_t = decltype(std::declval<T>()[std::declval<I>()]); // a[b]


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

}} // namespace cpp14concepts::details


#endif // CPP14CONCEPTS_DETAILS_UTILIY_HPP_