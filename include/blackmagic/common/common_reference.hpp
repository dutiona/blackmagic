#pragma once

#include "detector.hpp"
#include "traits_ext.hpp"

#include <type_traits>

/*
struct nil_ {
};

template <typename T>
struct id {
  template <typename...>
  using invoke = T;

  using type = T;
};

template <typename F, typename... Args>
using invoke = typename F::template invoke<Args...>;


template <template <typename...> class C, typename... Ts, template <typename...> class D = C>
id<D<Ts...>> try_defer_(int);
template <template <typename...> class C, typename... Ts>
nil_ try_defer_(long);

template <template <typename...> class C, typename... Ts>
using defer_ = decltype(try_defer_<C, Ts...>(0));

template <template <typename...> class C, typename... Ts>
struct defer : defer_<C, Ts...> {
};

template <typename... Ts>
using void_ = invoke<id<void>, Ts...>;
*/

namespace blackmagic::common {

// Public interface
template <typename T, typename U, typename TQual, typename UQual>
struct basic_common_reference {
};

template <typename... Ts>
struct common_reference {
};

template <typename... Ts>
using common_reference_t = typename common_reference<Ts...>::type;


namespace details {

namespace impl_ {
template <typename T>
T val_();

template <typename T, typename U>
using cond_expr_ = decltype(true ? val_<T>() : val_<U>());

template <typename T, typename U, typename = void>
struct valid_cond_expr_ : std::false_type {
};

template <typename T, typename U>
struct valid_cond_expr_<T, U, std::void_t<cond_expr_<T, U>>> : std::true_type {
};

template <typename T, typename U>
inline constexpr auto valid_cond_expr_v_ = valid_cond_expr_<T, U>::value;

template <typename T>
using has_type_ = typename T::type;

template <typename T>
struct xref_ {
  using type = T;
};
template <typename T>
struct xref_<T&&> {
  using type = std::add_rvalue_reference_t<typename xref_<T>::type>;
};
template <typename T>
struct xref_<T&> {
  using type = std::add_lvalue_reference_t<typename xref_<T>::type>;
};
template <typename T>
struct xref_<T const> {
  using type = std::add_const_t<T>;
};
template <typename T>
struct xref_<T volatile> {
  using type = std::add_volatile_t<T>;
};
template <typename T>
struct xref_<T const volatile> {
  using type = std::add_cv_t<T>;
};

} // namespace impl_


// Simple common reference
template <typename T, typename U, typename = void>
struct simple_common_reference {
};

template <typename T, typename U>
using simple_common_reference_t = typename simple_common_reference<T, U>::type;

namespace simple_common_reference_impl {

namespace lvalue {
// Lvalue impl
template <typename T, typename U, typename = void>
struct simple_common_reference_lvalue {
};

template <typename T, typename U>
struct simple_common_reference_lvalue<T, U, std::enable_if_t<impl_::valid_cond_expr_v_<T, U>>> {
  static constexpr bool is_const =
    std::disjunction_v<std::is_const<std::remove_reference_t<T>>, std::is_const<std::remove_reference_t<U>>>;

  static constexpr bool has_volatile =
    std::disjunction_v<std::is_volatile<std::remove_reference_t<T>>, std::is_volatile<std::remove_reference_t<U>>>;

  using type = std::add_lvalue_reference_t<
    apply_if_t<has_volatile, std::add_volatile_t, apply_if_t<is_const, std::add_const_t, impl_::cond_expr_<T, U>>>>;
};

template <typename T, typename U>
using simple_common_reference_lvalue_t = typename simple_common_reference_lvalue<T, U>::type;
} // namespace lvalue

namespace rvalue {
// Rvalue impl
template <typename T, typename U, typename = void>
struct simple_lvalue_common_from_rvalue {
};
template <typename T, typename U>
struct simple_lvalue_common_from_rvalue<
  T, U,
  std::void_t<lvalue::simple_common_reference_lvalue_t<std::add_lvalue_reference_t<std::remove_reference_t<T>>,
                                                     std::add_lvalue_reference_t<std::remove_reference_t<U>>>>>
  : lvalue::simple_common_reference_lvalue<std::add_lvalue_reference_t<std::remove_reference_t<T>>,
                                           std::add_lvalue_reference_t<std::remove_reference_t<U>>> {
};

template <typename T, typename U>
using simple_lvalue_common_from_rvalue_t = typename simple_lvalue_common_from_rvalue<T, U>::type;

template <typename T, typename U, typename = void>
struct simple_common_reference_rvalue {
};
template <typename T, typename U>
struct simple_common_reference_rvalue<T, U, std::void_t<simple_lvalue_common_from_rvalue_t<T, U>>> {
  using type = simple_lvalue_common_from_rvalue_t<T, U>;
};

template <typename T, typename U>
using simple_common_reference_rvalue_t = typename simple_common_reference_rvalue<T, U>::type;
} // namespace rvalue


namespace mixed {
// Mixed rvalue/lvalue impl
template <typename T, typename U>
using simple_common_ref_from_mixed =
  lvalue::simple_common_reference_lvalue<T, std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<U>>>>;

template <typename T, typename U>
using simple_common_ref_from_mixed_t = typename simple_common_ref_from_mixed<T, U>::type;

template <typename T, typename U, typename = void>
struct simple_common_reference_mixed {
};
template <typename T, typename U>
struct simple_common_reference_mixed<T, U, std::void_t<simple_common_ref_from_mixed_t<T, U>>> {
  using type = simple_common_ref_from_mixed_t<T, U>;
};

template <typename T, typename U>
using simple_common_reference_mixed_t = typename simple_common_reference_mixed<T, U>::type;
} // namespace mixed


// Predicates

// is lvalue ref
template <typename T, typename U>
inline constexpr auto is_lvalue_ref =
  std::conjunction_v<std::is_lvalue_reference<T>, std::is_lvalue_reference<U>,
                     common::is_detected<impl_::has_type_, lvalue::simple_common_reference_lvalue<T, U>>>;

// is rvalue ref
template <typename T, typename U>
inline constexpr auto is_rvalue_ref =
  std::conjunction_v<std::is_rvalue_reference<T>, std::is_rvalue_reference<U>,
                     common::is_detected<impl_::has_type_, rvalue::simple_lvalue_common_from_rvalue<T, U>>,
                     std::is_convertible<T, rvalue::simple_lvalue_common_from_rvalue_t<T, U>>,
                     std::is_convertible<U, rvalue::simple_lvalue_common_from_rvalue_t<T, U>>,
                     common::is_detected<impl_::has_type_, rvalue::simple_common_reference_rvalue<T, U>>>;

// is mixed
template <typename T, typename U>
inline constexpr auto is_mixed_ref_lhsrhs =
  std::conjunction_v<std::is_lvalue_reference<T>, std::is_rvalue_reference<U>,
                     common::is_detected<impl_::has_type_, mixed::simple_common_reference_mixed_t<T, U>>,
                     std::is_convertible<U, mixed::simple_common_reference_mixed_t<T, U>>>;

template <typename T, typename U>
inline constexpr auto is_mixed_ref_rhslhs =
  std::conjunction_v<std::is_rvalue_reference<T>, std::is_lvalue_reference<U>,
                     common::is_detected<impl_::has_type_, mixed::simple_common_reference_mixed_t<T, U>>,
                     std::is_convertible<T, mixed::simple_common_reference_mixed_t<T, U>>>;

} // namespace simple_common_reference_impl


// Simple common ref lvalue
template <typename T, typename U>
struct simple_common_reference<T, U, std::enable_if_t<simple_common_reference_impl::is_lvalue_ref<T, U>>> {
  using type = simple_common_reference_impl::lvalue::simple_common_reference_lvalue_t<T, U>;
};

// Simple common ref rvalue
template <typename T, typename U>
struct simple_common_reference<T, U,
                               std::enable_if_t<(!simple_common_reference_impl::is_lvalue_ref<
                                                   T, U> && simple_common_reference_impl::is_rvalue_ref<T, U>)>> {
  using type = simple_common_reference_impl::rvalue::simple_common_reference_rvalue_t<T, U>;
};

// Simple common ref mixed
template <typename T, typename U>
struct simple_common_reference<
  T, U,
  std::enable_if_t<(
    !simple_common_reference_impl::is_lvalue_ref<
      T,
      U> && !simple_common_reference_impl::is_rvalue_ref<T, U> && simple_common_reference_impl::is_mixed_ref_lhsrhs<T, U>)>> {
  using type = simple_common_reference_impl::mixed::simple_common_reference_mixed_t<T, U>;
};

template <typename T, typename U>
struct simple_common_reference<
  T, U,
  std::enable_if_t<(
    !simple_common_reference_impl::is_lvalue_ref<
      T,
      U> && !simple_common_reference_impl::is_rvalue_ref<T, U> && !simple_common_reference_impl::is_mixed_ref_lhsrhs<T, U> && simple_common_reference_impl::is_mixed_ref_rhslhs<T, U>)>> {
  using type = simple_common_reference_impl::mixed::simple_common_reference_mixed_t<U, T>;
};

namespace basic_common_reference_impl {
template <typename T, typename U>
using basic_common_reference_impl =
  basic_common_reference<common::remove_cvref_t<T>, common::remove_cvref_t<U>, typename impl_::xref_<T>::type,
                         typename impl_::xref_<U>::type>;

template <typename T, typename U>
using basic_common_reference_impl_t = typename basic_common_reference_impl<T, U>::type;

} // namespace basic_common_reference_impl


namespace common_reference_impl {
template <typename T, typename U, typename = void>
struct common_reference2 {
};

// T and U are both reference type and simple_common_reference type exists
template <typename T, typename U>
inline constexpr auto both_refs =
  std::conjunction_v<std::is_reference<T>, std::is_reference<U>,
                     common::is_detected<impl_::has_type_, simple_common_reference<T, U>>>;

//  basic_common_reference exists
template <typename T, typename U>
inline constexpr auto basic_common_reference_exists =
  is_detected_v<impl_::has_type_, basic_common_reference_impl::basic_common_reference_impl<T, U>>;

// cond_expr is valid
template <typename T, typename U>
inline constexpr auto cond_expr_is_valid = impl_::valid_cond_expr_v_<T, U>;

// std::common_type is valid
template <typename T, typename U>
inline constexpr auto common_type_valid = is_detected_v<impl_::has_type_, std::common_type<T, U>>;

template <typename T, typename U>
struct common_reference2<T, U, std::enable_if_t<both_refs<T, U>>> {
  using type = simple_common_reference_t<T, U>;
};

template <typename T, typename U>
struct common_reference2<T, U, std::enable_if_t<(!both_refs<T, U> && basic_common_reference_exists<T, U>)>> {
  using type = basic_common_reference_impl::basic_common_reference_impl_t<T, U>;
};

template <typename T, typename U>
struct common_reference2<
  T, U, std::enable_if_t<(!both_refs<T, U> && !basic_common_reference_exists<T, U> && cond_expr_is_valid<T, U>)>> {
  using type = impl_::cond_expr_<T, U>;
};

template <typename T, typename U>
struct common_reference2<
  T, U,
  std::enable_if_t<(
    !both_refs<T,
               U> && !basic_common_reference_exists<T, U> && !cond_expr_is_valid<T, U> && common_type_valid<T, U>)>> {
  using type = std::common_type_t<T, U>;
};

} // namespace common_reference_impl

} // namespace details


// Common reference implementation
template <typename T>
struct common_reference<T> {
  using type = T;
};

template <typename T, typename U>
struct common_reference<T, U> {
  using type = typename details::common_reference_impl::common_reference2<T, U>::type;
};

template <typename T, typename U, typename... Vs>
struct common_reference<T, U, Vs...> {
  using type = common_reference_t<typename details::common_reference_impl::common_reference2<T, U>::type, Vs...>;
};


} // namespace blackmagic::common
