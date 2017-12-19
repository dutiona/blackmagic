#pragma once

#ifndef METAPROG_CPT_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
#define METAPROG_CPT_BASIC_DETAILS_CONCEPTS_IMPL_HPP_

#include "../traits.hpp"

#include <type_traits>

namespace cpt { namespace concepts { namespace basic { namespace details {

namespace traits = traits::basic;

// default constructible
template <bool SilentFailure, typename T, typename = void>
struct default_constructible_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the default_constructible concept.");
};
template <bool SilentFailure, typename T>
struct default_constructible_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_default_constructible<T>, traits::is_nothrow_default_constructible<T>,
                                      traits::is_trivially_default_constructible<T>>>> : std::true_type {
};

// move constructible
template <bool SilentFailure, typename T, typename = void>
struct move_constructible_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the move_constructible concept.");
};
template <bool SilentFailure, typename T>
struct move_constructible_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_move_constructible<T>, traits::is_nothrow_move_constructible<T>,
                                      traits::is_trivially_move_constructible<T>>>> : std::true_type {
};

// copy constructible
template <bool SilentFailure, typename T, typename = void>
struct copy_constructible_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the copy_constructible concept.");
};
template <bool SilentFailure, typename T>
struct copy_constructible_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_copy_constructible<T>, traits::is_nothrow_copy_constructible<T>,
                                      traits::is_trivially_copy_constructible<T>>>> : std::true_type {
};

// move assignable
template <bool SilentFailure, typename T, typename = void>
struct move_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the move_assignable concept.");
};
template <bool SilentFailure, typename T>
struct move_assignable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_move_assignable<T>, traits::is_nothrow_move_assignable<T>,
                                      traits::is_trivially_move_assignable<T>>>> : std::true_type {
};

// copy assignable
template <bool SilentFailure, typename T, typename = void>
struct copy_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the copy_assignable concept.");
};
template <bool SilentFailure, typename T>
struct copy_assignable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_copy_assignable<T>, traits::is_nothrow_copy_assignable<T>,
                                      traits::is_trivially_copy_assignable<T>>>> : std::true_type {
};

// destructible
template <bool SilentFailure, typename T, typename = void>
struct destructible_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the destructible concept.");
};
template <bool SilentFailure, typename T>
struct destructible_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_destructible<T>, traits::is_nothrow_destructible<T>,
                                      traits::is_trivially_destructible<T>>>> : std::true_type {
};

}}}} // namespace cpt::concepts::basic::details

#endif // CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
