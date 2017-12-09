#pragma once

#ifndef CONCEPTS_LAYOUT_CONCEPTS_HPP_
#define CONCEPTS_LAYOUT_CONCEPTS_HPP_
/**
 *
 *
 * trivially copyable : class with trivial copy, assignment and destructor
 *
 * trivial : class with trivial constructors, assignment and destructor
 *
 * standard layout : non-virtual class containing only other StandardLayout
 * members, all with the same access control
 *
 * POD : POD (Plain Old Data) structure, compatible with C struct
 *
 */

#include "details/concepts_impl.hpp"

namespace concepts { namespace layout {

// trivially copyable
template <typename T>
constexpr bool trivially_copyable = details::trivially_copyable_v<T>;

// trivial
template <typename T>
constexpr bool trivial = details::trivial_v<T>;

// standard layout
template <typename T>
constexpr bool standard_layout = details::standard_layout_v<T>;

// POD
template <typename T>
constexpr bool pod = details::pod_v<T>;

}} // namespace concepts::layout

#endif // CONCEPTS_LAYOUT_CONCEPTS_HPP_
