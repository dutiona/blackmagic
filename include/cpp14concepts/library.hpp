#pragma once

#ifndef CPP14CONCEPTS_LIBRARY_HPP_
#  define CPP14CONCEPTS_LIBRARY_HPP_
/**
 *
 * EqualityComparable : operator== is an equivalence relation
 *
 * LessThanComparable : operator< is a strict weak ordering relation
 *
 * Swappable : can be swapped with an unqualified non-member function call
 * swap()
 *
 * ValueSwappable : an Iterator that dereferences to a Swappable type
 *
 * NullablePointer : a pointer-like type supporting a null value
 *
 * Hash : a FunctionObject that for inputs with different values has a low
 * probability of giving the same output
 *
 * FunctionObject : an object that can be called with the function call syntax Callable : a type for which the invoke
 * operation is defined
 *
 * Predicate : a FunctionObject that returns a value convertible to bool
 * for one argument without modifying it
 *
 * BinaryPredicate : a FunctionObject that returns a value convertible to bool for two arguments without modifying them
 *
 * Compare : a BinaryPredicate that establishes an ordering relation
 *
 */

#  include "cpp17additions.hpp"
#  include "iterator.hpp"

#  include "details/library.hpp"

#  include <type_traits>
#  include <utility>

namespace cpp14concepts {

// EqualityComparable
template <typename T>
constexpr bool EqualityComparable = std::conjunction<std::is_convertible<details::equality_t<T>, bool>::value,
                                                     std::is_convertible<details::inequality_t<T>, bool>::value>::value;

// LessThanComparable
template <typename T>
constexpr bool LessThanComparable = std::is_convertible<details::less_than_t<T>, bool>::value;

// Swappable
template <typename T, typename U = T>
constexpr bool Swappable = cpp17additions::is_swappable_with_v<T, U>;

// ValueSwappable
template <typename T, typename U = T>
constexpr bool ValueSwappable = std::conjunction<
  Iterator<T>, Iterator<U>,
  cpp17additions::is_swappable_with_v<details::dereferenceable_t<T>, details::dereferenceable_t<U>>>::value;

// NullablePointer
template <typename T>
constexpr bool NullablePointer = std::conjunction<
  EqualityComparable<T>, DefaultConstructible<T>, CopyConstructible<T>, CopyAssignable<T>, Destructible<T>,
  std::is_convertible<T, bool>::value, std::is_same<details::constructible_t<T, std::nullptr_t>, T>::value,
  std::is_convertible<details::constructible_t<T, std::nullptr_t>, std::nullptr_t>::value,
  std::is_same<details::assignable_t<T, std::nullptr_t>, std::add_lvalue_reference_t<T>>::value,
  std::is_convertible<details::assignable_t<T, std::nullptr_t>, std::nullptr_t>::value,
  std::is_convertible<std::add_rvalue_reference_t<details::constructible_t<T, std::nullptr_t>>, std::nullptr_t>::value,
  std::is_convertible<details::inequality_t<T>, bool>::value,
  std::is_convertible<details::equality_t<T, std::nullptr_t>, bool>::value,
  std::is_convertible<details::inequality_t<T, std::nullptr_t>, bool>::value,
  std::is_convertible<details::equality_t<std::nullptr_t, T>, bool>::value,
  std::is_convertible<details::inequality_t<std::nullptr_t, T>, bool>::value>::value;

// Hash
template <typename T, typename Key>
constexpr bool Hash = std::conjunction<FunctionObject<T>, CopyConstructible<T>, Destructible<T>,
                                       std::is_same<details::function_call_t<T, Key>, std::size_t>::value>::value;

// FunctionObject
template <typename T, typename... Args>
constexpr bool FunctionObject =
  std::conjunction<std::is_object<T>::value, cpp17additions::is_detected_v<details::function_call_t, T>>::value;

// Predicate
template <typename T, typename... Args>
constexpr bool Predicate =
  std::conjunction<FunctionObject<T, Args...>,
                   std::is_convertible<details::function_call_t<T, Args...>, bool>::value>::value;

// BinaryPredicate
template <typename T, typename Arg1, typename Arg2>
constexpr bool BinaryPredicate =
  std::disjunction<std::conjunction<Iterator<Arg1>, Iterator<Arg2>, Predicate<T, Arg1, Arg2>>::value,
                   std::conjunction<Iterator<Arg1>, CopyConstructible<Arg2>, Predicate<T, Arg1, Arg2>>::value>::value;

// Compare
template <typename T, typename Arg1, typename Arg2>
constexpr bool Compare =
  std::conjunction<BinaryPredicate<T, Arg1, Arg2>, std::is_same<details::function_call_t<T, Arg1, Arg2>,
                                                                details::compare_equiv_t<T, Arg1, Arg2>>::value>::value;

} // namespace cpp14concepts

#endif // CPP14CONCEPTS_LIBRARY_HPP_
