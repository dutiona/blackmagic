#pragma once

#ifndef CONCEPTS_TRAITS_ITERATOR_HPP_
#define CONCEPTS_TRAITS_ITERATOR_HPP_

#include <iterator>
#include <type_traits>

namespace concepts { namespace traits {

template <typename T>
using value_type_t = typename std::iterator_traits<T>::value_type;

template <typename T>
using difference_type_t = typename std::iterator_traits<T>::difference_type;

template <typename T>
using reference_t = typename std::iterator_traits<T>::reference;

template <typename T>
using pointer_t = typename std::iterator_traits<T>::pointer;

template <typename T>
using iterator_category_t = typename std::iterator_traits<T>::iterator_category;

template <typename T>
using dereferenceable_post_incrementable_t = decltype(*std::declval<T>()++); // *a++

template <typename T>
using dereferenceable_post_decrementable_t = decltype(*std::declval<T>()--); // *a--

template <typename T>
using dereferenceable_pre_incrementable_t = decltype(*++std::declval<T>()); // *++a

template <typename T>
using dereferenceable_pre_decrementable_t = decltype(*--std::declval<T>()); // *--a

template <typename T, typename U = T>
using dereferenceable_assignable_t = decltype(*std::declval<T>() = std::declval<U>()); // *a = b

template <typename T, typename U = T>
using dereferenceable_assignable_post_incrementable_t = decltype(*std::declval<T>()++ = std::declval<U>()); // *a++ = b

template <typename T, typename U = T>
using dereferenceable_assignable_post_decrementable_t = decltype(*std::declval<T>()-- = std::declval<U>()); // *a-- = b

template <typename T, typename U = T>
using dereferenceable_assignable_pre_incrementable_t = decltype(*++std::declval<T>() = std::declval<U>()); // *++a = b

template <typename T, typename U = T>
using dereferenceable_assignable_pre_decrementable_t = decltype(*--std::declval<T>() = std::declval<U>()); // *--a = b

}} // namespace concepts::traits


#endif // CONCEPTS_TRAITS_ITERATOR_HPP_