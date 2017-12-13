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
template <bool SilentFailure, typename T>
using default_constructible = details::default_constructible_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using default_constructible_t = typename default_constructible<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool default_constructible_v = default_constructible<SilentFailure, T>::value;

// move constructible
template <bool SilentFailure, typename T>
using move_constructible = details::move_constructible_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using move_constructible_t = typename move_constructible<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool move_constructible_v = move_constructible<SilentFailure, T>::value;

// copy constructible
template <bool SilentFailure, typename T>
using copy_constructible = details::copy_constructible_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using copy_constructible_t = typename copy_constructible<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool copy_constructible_v = copy_constructible<SilentFailure, T>::value;

// move assignable
template <bool SilentFailure, typename T>
using move_assignable = details::move_assignable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using move_assignable_t = typename move_assignable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool move_assignable_v = move_assignable<SilentFailure, T>::value;

// copy assignable
template <bool SilentFailure, typename T>
using copy_assignable = details::copy_assignable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using copy_assignable_t = typename copy_assignable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool copy_assignable_v = copy_assignable<SilentFailure, T>::value;

// destructible
template <bool SilentFailure, typename T>
using destructible = details::destructible_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using destructible_t = typename destructible<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool destructible_v = destructible<SilentFailure, T>::value;

}} // namespace concepts::basic

#endif // CONCEPTS_BASIC_CONCEPTS_HPP_
