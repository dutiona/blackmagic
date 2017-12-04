#pragma once

#ifndef CONCEPTS_BASIC_CONCEPTS_HPP_
#define CONCEPTS_BASIC_CONCEPTS_HPP_
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

#include "details/concepts_impl.hpp"

namespace concepts { namespace basic {

// DefaultConstructible
template <typename T>
constexpr bool DefaultConstructible = details::default_constructible_v<T>;

// MoveConstructible
template <typename T>
constexpr bool MoveConstructible = details::move_constructible_v<T>;

// CopyConstructible
template <typename T>
constexpr bool CopyConstructible = std::is_copy_assignable_v<T>;

// MoveAssignable
template <typename T>
constexpr bool MoveAssignable = std::is_move_assignable_v<T>;

// CopyAssignable
template <typename T>
constexpr bool CopyAssignable = std::is_copy_assignable_v<T>;

// Destructible
template <typename T>
constexpr bool Destructible = std::is_destructible_v<T>;

}} // namespace concepts::basic

#endif // CONCEPTS_BASIC_CONCEPTS_HPP_