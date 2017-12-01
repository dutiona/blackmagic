#pragma once

#ifndef CPP14CONCEPTS_DETAILS_ITERATOR_HPP_
#  define CPP14CONCEPTS_DETAILS_ITERATOR_HPP_

#  include <iterator>
#  include <type_traits>

namespace cpp14concepts { namespace details {

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

}} // namespace cpp14concepts::details


#endif // CPP14CONCEPTS_DETAILS_ITERATOR_HPP_