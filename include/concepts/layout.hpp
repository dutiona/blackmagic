#pragma once

#ifndef CONCEPTS_LAYOUT_HPP_
#define CONCEPTS_LAYOUT_HPP_
/**
 *
 *
 * TriviallyCopyable : class with trivial copy, assignment and destructor
 *
 * TrivialType : class with trivial constructors, assignment and destructor
 *
 * StandardLayoutType : non-virtual class containing only other StandardLayout
 * members, all with the same access control
 *
 * PODType : POD (Plain Old Data) structure, compatible with C struct
 *
 */

#include <type_traits>

namespace concepts {

// TriviallyCopyable
template <typename T>
constexpr bool TriviallyCopyable = std::is_trivially_copyable<T>::value;

// TrivialType
template <typename T>
constexpr bool TrivialType = std::is_trivial<T>::value;

// MoveConstructible
template <typename T>
constexpr bool CopyConstructible = std::is_copy_assignable<T>::value;

// StandardLayoutType
template <typename T>
constexpr bool StandardLayoutType = std::is_standard_layout<T>::value;

// PODType
template <typename T>
constexpr bool PODType = std::is_pod<T>::value;
} // namespace concepts

#endif // CONCEPTS_LAYOUT_HPP_
