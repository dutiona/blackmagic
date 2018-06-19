#pragma once

#include "detector.hpp"
#include "traits_ext.hpp"

#include <type_traits>

namespace blackmagic::common {

struct NOTYPE {
};

template <typename T, typename U, typename TQual, typename UQual>
struct basic_common_reference {
};

template <typename... Ts>
struct common_reference {
};

template <typename... Ts>
using common_reference_t = typename common_reference<Ts...>::type;


namespace details {

// Impl details
template <typename T>
T val();

template <typename T, typename U>
using cond_expr = decltype(false ? val<T>() : val<U>());

template <typename T, typename U, typename = void>
struct valid_cond_expr : std::false_type {
};

template <typename T, typename U>
struct valid_cond_expr<T, U, std::void_t<cond_expr<T, U>>> : std::true_type {
};

template <typename T, typename U>
inline constexpr auto valid_cond_expr_v = valid_cond_expr<T, U>::value;

// Simple common ref
template <typename T, typename U, typename = void>
struct simple_common_reference {
};

template <typename T, typename U>
using simple_common_reference_t = typename simple_common_reference<T, U>::type;


// Lvalue impl
template <typename T, typename U>
struct simple_common_reference_lvalue {
  static constexpr bool is_const =
    std::disjunction_v<std::is_const<std::remove_reference_t<T>>, std::is_const<std::remove_reference_t<U>>>;
  static constexpr bool has_volatile =
    std::disjunction_v<std::is_volatile<std::remove_reference_t<T>>, std::is_volatile<std::remove_reference_t<U>>>;
  using type = std::add_lvalue_reference_t<
    apply_if_t<has_volatile, std::add_volatile_t, apply_if_t<is_const, std::add_const_t, cond_expr<T, U>>>>;
};

template <typename T, typename U>
using simple_common_reference_lvalue_t = typename simple_common_reference_lvalue<T, U>::type;

// Simple common ref lvalue
template <typename T, typename U>
struct simple_common_reference<
  T, U, std::enable_if_t<std::conjunction_v<std::is_lvalue_reference<T>, std::is_lvalue_reference<U>>>> {
  using type = simple_common_reference_lvalue_t<T, U>;
};


// Rvalue impl
template <typename T, typename U>
using simple_lvalue_common_from_rvalue =
  simple_common_reference_lvalue<std::add_lvalue_reference_t<std::remove_reference_t<T>>,
                                 std::add_lvalue_reference_t<std::remove_reference_t<U>>>;

template <typename T, typename U>
using simple_lvalue_common_from_rvalue_t = typename simple_lvalue_common_from_rvalue<T, U>::type;

template <typename T, typename U>
struct simple_common_reference_rvalue {
  using type = simple_lvalue_common_from_rvalue_t<T, U>;
};

template <typename T, typename U>
using simple_common_reference_rvalue_t = typename simple_common_reference_rvalue<T, U>::type;

// Simple common ref rvalue
template <typename T, typename U>
struct simple_common_reference<
  T, U,
  std::enable_if_t<std::conjunction_v<std::is_rvalue_reference<T>, std::is_rvalue_reference<U>,
                                      std::is_convertible<T, simple_lvalue_common_from_rvalue_t<T, U>>,
                                      std::is_convertible<U, simple_lvalue_common_from_rvalue_t<T, U>>>>> {
  using type = simple_common_reference_rvalue_t<T, U>;
};


// Mixed rvalue/lvalue impl
template <typename T, typename U>
using simple_common_ref_from_mixed =
  simple_common_reference_lvalue<T, std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<U>>>>;

template <typename T, typename U>
using simple_common_ref_from_mixed_t = typename simple_common_ref_from_mixed<T, U>::type;

template <typename T, typename U>
struct simple_common_reference_mixed {
  using type = simple_common_ref_from_mixed_t<T, U>;
};

template <typename T, typename U>
using simple_common_reference_mixed_t = typename simple_common_reference_mixed<T, U>::type;

// Simple common ref mixed
template <typename T, typename U>
struct simple_common_reference<
  T, U,
  std::enable_if_t<std::conjunction_v<std::is_lvalue_reference<T>, std::is_rvalue_reference<U>,
                                      std::is_convertible<U, simple_common_reference_mixed_t<T, U>>>>> {
  using type = simple_common_reference_mixed_t<T, U>;
};

template <typename T, typename U>
struct simple_common_reference<
  T, U, std::enable_if_t<std::conjunction_v<std::is_rvalue_reference<T>, std::is_lvalue_reference<U>>>>
  : simple_common_reference<U, T> {
};

template <typename T>
struct _xref {
  using type = T;
};
template <typename T>
struct _xref<T&&> {
  using type = std::add_rvalue_reference_t<typename _xref<T>::type>;
};
template <typename T>
struct _xref<T&> {
  using type = std::add_lvalue_reference_t<typename _xref<T>::type>;
};
template <typename T>
struct _xref<T const> {
  using type = std::add_const_t<T>;
};
template <typename T>
struct _xref<T volatile> {
  using type = std::add_volatile_t<T>;
};
template <typename T>
struct _xref<T const volatile> {
  using type = std::add_cv_t<T>;
};

template <typename T, typename U>
using basic_common_reference_impl =
  basic_common_reference<remove_cvref_t<T>, remove_cvref_t<U>, typename _xref<T>::type, typename _xref<U>::type>;

template <typename T, typename U>
using basic_common_reference_impl_t = typename basic_common_reference_impl<T, U>::type;

template <typename T>
using has_type_ = typename T::type;

template <typename T, typename U, typename = void>
struct common_reference2 {
};

// T and U are both reference type and simple_common_reference type exists
template <typename T, typename U>
inline constexpr auto both_refs =
  std::conjunction_v<std::is_reference<T>, std::is_reference<U>, is_detected<has_type_, simple_common_reference<T, U>>>;

//  basic_common_reference exists
template <typename T, typename U>
inline constexpr auto basic_common_reference_exists = is_detected_v<has_type_, basic_common_reference_impl<T, U>>;

// cond_expr is valid
template <typename T, typename U>
inline constexpr auto cond_expr_is_valid = valid_cond_expr_v<T, U>;

// std::common_type is valid
template <typename T, typename U>
inline constexpr auto common_type_valid = is_detected_v<has_type_, std::common_type<T, U>>;

template <typename T, typename U>
struct common_reference2<T, U, std::enable_if_t<both_refs<T, U>>> {
  using type = simple_common_reference_t<T, U>;
};

template <typename T, typename U>
struct common_reference2<T, U, std::enable_if_t<(!both_refs<T, U> && basic_common_reference_exists<T, U>)>> {
  using type = basic_common_reference_impl_t<T, U>;
};

template <typename T, typename U>
struct common_reference2<
  T, U, std::enable_if_t<(!both_refs<T, U> && !basic_common_reference_exists<T, U> && cond_expr_is_valid<T, U>)>> {
  using type = cond_expr<T, U>;
};

template <typename T, typename U>
struct common_reference2<
  T, U,
  std::enable_if_t<(
    !both_refs<T,
               U> && !basic_common_reference_exists<T, U> && !cond_expr_is_valid<T, U> && common_type_valid<T, U>)>> {
  using type = std::common_type_t<T, U>;
};

} // namespace details


template <typename T>
struct common_reference<T> {
  using type = T;
};

template <typename T, typename U>
struct common_reference<T, U> {
  using type = typename details::common_reference2<T, U>::type;
};

template <typename T, typename U, typename... Vs>
struct common_reference<T, U, Vs...> {
  using type = common_reference_t<typename details::common_reference2<T, U>::type, Vs...>;
};


} // namespace blackmagic::common
