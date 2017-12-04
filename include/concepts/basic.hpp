#pragma once

#ifndef CONCEPTS_BASIC_HPP_
#  define CONCEPTS_BASIC_HPP_
/**
 *
 * DefaultConstructible : specifies that an object of the type can be default
 * constructed
 *
 * MoveConstructible : specifies that an object of the type can be constructed
 * from rvalue
 *
 * CopyConstructible : specifies that an object of the type can be constructed
 * from lvalue
 *
 * MoveAssignable : specifies that an object of the type can be assigned from
 * rvalue
 *
 * CopyAssignable : specifies that an object of the type can be assigned from
 * lvalue
 *
 * Destructible : specifies that an object of the type can be destroyed
 *
 */

#  include <type_traits>

namespace concepts {

// DefaultConstructible
template <typename T>
constexpr bool DefaultConstructible = std::is_default_constructible<T>::value;

// MoveConstructible
template <typename T>
constexpr bool MoveConstructible = std::is_move_constructible<T>::value;

// MoveConstructible
template <typename T>
constexpr bool CopyConstructible = std::is_copy_assignable<T>::value;

// MoveAssignable
template <typename T>
constexpr bool MoveAssignable = std::is_move_assignable<T>::value;

// CopyAssignable
template <typename T>
constexpr bool CopyAssignable = std::is_copy_assignable<T>::value;

// Destructible
template <typename T>
constexpr bool Destructible = std::is_destructible<T>::value;
} // namespace concepts

#endif // CONCEPTS_BASIC_HPP_