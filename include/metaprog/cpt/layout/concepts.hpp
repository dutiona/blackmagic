#pragma once

#ifndef METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
#define METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
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
 */

#include "details/concepts_impl.hpp"

namespace cpt { namespace concepts { namespace layout {

// trivially copyable
template <bool SilentFailure, typename T>
using trivially_copyable = details::trivially_copyable_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using trivially_copyable_t = typename trivially_copyable<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool trivially_copyable_v = trivially_copyable<SilentFailure, T>::value;

// trivial
template <bool SilentFailure, typename T>
using trivial = details::trivial_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using trivial_t = typename trivial<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool trivial_v = trivial<SilentFailure, T>::value;

// standard layout
template <bool SilentFailure, typename T>
using standard_layout = details::standard_layout_impl<SilentFailure, T>;
template <bool SilentFailure, typename T>
using standard_layout_t = typename standard_layout<SilentFailure, T>::type;
template <bool SilentFailure, typename T>
constexpr bool standard_layout_v = standard_layout<SilentFailure, T>::value;

}}} // namespace cpt::concepts::layout

#endif // METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
