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
struct trivially_copyable {
  template <bool SilentFailure, typename T>
  using type = details::trivially_copyable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// trivial
struct trivial {
  template <bool SilentFailure, typename T>
  using type = details::trivial_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// standard layout
struct standard_layout {
  template <bool SilentFailure, typename T>
  using type = details::standard_layout_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

}}} // namespace cpt::concepts::layout

#endif // METAPROG_CPT_LAYOUT_CONCEPTS_HPP_
