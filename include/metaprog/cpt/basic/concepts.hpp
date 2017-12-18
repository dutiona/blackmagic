#pragma once

#ifndef METAPROG_CPT_BASIC_CONCEPTS_HPP_
#define METAPROG_CPT_BASIC_CONCEPTS_HPP_

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

namespace cpt { namespace concepts { namespace basic {

// default constructible
struct default_constructible {
  template <bool SilentFailure, typename T>
  using type = details::default_constructible_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// move constructible
struct move_constructible {
  template <bool SilentFailure, typename T>
  using type = details::move_constructible_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// copy constructible
struct copy_constructible {
  template <bool SilentFailure, typename T>
  using type = details::copy_constructible_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};


// move assignable
struct move_assignable {
  template <bool SilentFailure, typename T>
  using type = details::move_assignable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// copy assignable
struct copy_assignable {
  template <bool SilentFailure, typename T>
  using type = details::copy_assignable_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

// destructible
struct destructible {
  template <bool SilentFailure, typename T>
  using type = details::destructible_impl<SilentFailure, T>;
  template <bool SilentFailure, typename T>
  using underlying_type = typename type<SilentFailure, T>::type;
  template <bool SilentFailure, typename T>
  static constexpr bool value = type<SilentFailure, T>::value;
};

}}} // namespace cpt::concepts::basic

#endif // METAPROG_CPT_BASIC_CONCEPTS_HPP_
