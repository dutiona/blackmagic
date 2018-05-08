#pragma once

/**
 *
 * Iterator : general concept to access data within some data structure
 *
 * InputIterator : iterator that can be used to read data
 *
 * OutputIterator : iterator that can be used to write data
 *
 * ForwardIterator : iterator that can be used to read data multiple times
 *
 * BidirectionalIterator : iterator that can be both incremented and decremented
 *
 * RandomAccessIterator : iterator that can be advanced in constant time
 *
 * ContiguousIterator : iterator to contiguously allocated elements
 *
 */

#include "basic.hpp"
#include "helpers.hpp"
#include "library.hpp"

#include "traits/iterator.hpp"
#include "traits/utility.hpp"

#include <type_traits>
#include <utility>

namespace concepts {

// Iterator
template <typename T>
constexpr bool Iterator = std::conjunction<
  CopyConstructible<T>, CopyAssignable<T>, Destructible<T>, Swappable<std::add_lvalue_reference_t<T>>,
  cpp17additions::is_detected_v<details::value_type_t, T>, cpp17additions::is_detected_v<details::difference_type_t, T>,
  cpp17additions::is_detected_v<details::reference_t, T>, cpp17additions::is_detected_v<details::pointer_t, T>,
  cpp17additions::is_detected_v<details::iterator_category_t, T>,
  cpp17additions::is_detected_v<details::dereferenceable_t, T>,
  std::is_same<details::pre_incrementable_t<T>, details::reference_t<T>>::value>::value;

// InputIterator
template <typename T>
constexpr bool InputIterator = std::conjunction<
  Iterator<T>, EqualityComparable<T>, cpp17additions::is_detected_v<details::post_incrementable_t, T>,
  std::is_convertible<details::equality_t<T>, bool>::value,
  std::is_convertible<details::reference_t<T>, details::value_type_t<T>>::value,
  std::is_convertible<details::dereferenceable_post_incrementable_t<T>, details::value_type_t<T>>::value>::value;

template <typename T>
constexpr bool OutputIterator =
  std::conjunction<Iterator<T>, std::is_class<T>::value || std::is_pointer<T>::value,
                   std::is_convertible<details::post_incrementable_t<T>, details::reference_t<T>>::value,
                   std::is_same<details::pre_incrementable_t<T>, details::reference_t<T>>::value,
                   cpp17additions::is_detected_v<details::dereferenceable_assignable_t, T>,
                   cpp17additions::is_detected_v<details::dereferenceable_assignable_post_incrementable_t, T>>::value;

// ForwardIterator
// BidirectionalIterator
// RandomAccessIterator
// ContiguousIterator

} // namespace concepts
