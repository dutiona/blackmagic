#pragma once

#ifndef CONCEPTS_BASIC_CONCEPTS_HPP_
#define CONCEPTS_BASIC_CONCEPTS_HPP_

/**
 *
 * default constructible : specifies that an object of the type can be default
 * constructed
 *
 * move constructible : specifies that an object of the type can be constructed
 * from rvalue
 *
 * copy constructible : specifies that an object of the type can be constructed
 * from lvalue
 *
 * move assignable : specifies that an object of the type can be assigned from
 * rvalue
 *
 * copy assignable : specifies that an object of the type can be assigned from
 * lvalue
 *
 * destructible : specifies that an object of the type can be destroyed
 *
 */

#include "details/concepts_impl.hpp"

namespace concepts { namespace basic {

// default constructible
template <typename T>
constexpr bool default_constructible = details::default_constructible_v<T>;

// move constructible
template <typename T>
constexpr bool move_constructible = details::move_constructible_v<T>;

// copy constructible
template <typename T>
constexpr bool copy_constructible = details::copy_constructible_v<T>;

// move assignable
template <typename T>
constexpr bool move_assignable = details::move_assignable_v<T>;

// copy assignable
template <typename T>
constexpr bool copy_assignable = details::copy_assignable_v<T>;

// destructible
template <typename T>
constexpr bool destructible = details::destructible_v<T>;

}} // namespace concepts::basic

#endif // CONCEPTS_BASIC_CONCEPTS_HPP_