#pragma once

#include "core/details.hpp"

#include "engine.hpp"

#include <string_view>

namespace metaprog::concepts { inline namespace core {

using namespace std::literals;

inline constexpr auto Same = make_concept_item_from_predicate<details::same_predicate>("Same"sv);

inline constexpr auto ImplicitlyConvertibleTo =
  make_concept_item_from_predicate<details::implicitly_convertible_to_predicate>("ImplicitlyConvertibleTo"sv);

inline constexpr auto ExplicitlyConvertibleTo =
  make_concept_item_from_predicate<details::explicitly_convertible_to_predicate>("ExplicitlyConvertibleTo"sv);

inline constexpr auto ConvertibleTo = make_concept_map(ImplicitlyConvertibleTo, ExplicitlyConvertibleTo);

/*
struct DerivedFrom {
  template <typename T, typename U>
  auto requires_() -> decltype(concepts::valid_expr(
    concepts::is_true(std::is_base_of<U, T>{}),
    concepts::is_true(std::is_convertible<meta::_t<std::remove_cv<T>>*, meta::_t<std::remove_cv<U>>*>{})));
};

struct CommonReference {
  template <typename T, typename U, typename... Rest>
  using reference_t = common_reference_t<T, U, Rest...>;

  template <typename T, typename U>
  auto requires_() -> decltype(concepts::valid_expr(concepts::model_of<Same, reference_t<T, U>, reference_t<U, T>>(),
                                                    concepts::model_of<ConvertibleTo, T, reference_t<T, U>>(),
                                                    concepts::model_of<ConvertibleTo, U, reference_t<T, U>>()));

  template <typename T, typename U, typename... Rest, typename CommonReference_ = CommonReference>
  auto requires_()
    -> decltype(concepts::valid_expr(concepts::model_of<CommonReference_, T, U>(),
                                     concepts::model_of<CommonReference_, reference_t<T, U>, Rest...>()));
};

struct Common {
  template <typename T, typename U, typename... Rest>
  using value_t = common_type_t<T, U, Rest...>;

  template <typename T, typename U>
  auto requires_() -> decltype(concepts::valid_expr(concepts::is_true(std::is_same<uncvref_t<T>, uncvref_t<U>>{})));

  template <typename T, typename U>
  auto requires_() -> decltype(concepts::valid_expr(
    concepts::is_false(std::is_same<uncvref_t<T>, uncvref_t<U>>{}),
    concepts::model_of<Same, value_t<T, U>, value_t<U, T>>(), concepts::model_of<ConvertibleTo, T, value_t<T, U>>(),
    concepts::model_of<ConvertibleTo, U, value_t<T, U>>(),
    concepts::model_of<CommonReference, detail::as_cref_t<T>, detail::as_cref_t<U>>(),
    concepts::model_of<CommonReference, value_t<T, U>&,
                       common_reference_t<detail::as_cref_t<T>, detail::as_cref_t<U>>>()));

  template <typename T, typename U, typename... Rest, typename Common_ = Common>
  auto requires_() -> decltype(concepts::valid_expr(concepts::model_of<Common_, T, U>(),
                                                    concepts::model_of<Common_, value_t<T, U>, Rest...>()));
};

struct Integral {
  template <typename T>
  auto requires_() -> decltype(concepts::valid_expr(concepts::is_true(std::is_integral<T>{})));
};

struct SignedIntegral : refines<Integral> {
  template <typename T>
  auto requires_() -> decltype(concepts::valid_expr(concepts::is_true(std::is_signed<T>{})));
};

struct UnsignedIntegral : refines<Integral> {
  template <typename T>
  auto requires_() -> decltype(concepts::valid_expr(concepts::is_false(std::is_signed<T>{})));
};

struct Assignable {
  template <typename T, typename U>
  auto requires_(T&& t, U&& u)
    -> decltype(concepts::valid_expr(concepts::is_true(std::is_lvalue_reference<T>{}),
                                     concepts::model_of<CommonReference, detail::as_cref_t<T>, detail::as_cref_t<U>>(),
                                     concepts::has_type<T>((T &&) t = (U &&) u)));
};

struct Swappable {
  template <typename T>
  auto requires_(T&& t) -> decltype(concepts::valid_expr(((void) ranges::swap((T &&) t, (T &&) t), 42)));

  template <typename T, typename U>
  auto requires_(T&& t, U&& u)
    -> decltype(concepts::valid_expr(concepts::model_of<Swappable, T>(), concepts::model_of<Swappable, U>(),
                                     concepts::model_of<CommonReference, detail::as_cref_t<T>, detail::as_cref_t<U>>(),
                                     ((void) ranges::swap((T &&) t, (U &&) u), 42),
                                     ((void) ranges::swap((U &&) u, (T &&) t), 42)));
};


*/

}} // namespace metaprog::concepts::core

/*

template<typename ...Ts>
using Same = concepts::Same::same_t<Ts...>; // This handles void better than using the Same concept

template<typename T, typename U>
using ImplicitlyConvertibleTo =
concepts::models<concepts::ImplicitlyConvertibleTo, T, U>;

template<typename T, typename U>
using ExplicitlyConvertibleTo =
concepts::models<concepts::ExplicitlyConvertibleTo, T, U>;

template<typename T, typename U>
using ConvertibleTo = concepts::models<concepts::ConvertibleTo, T, U>;

template<typename T, typename U>
using DerivedFrom = concepts::models<concepts::DerivedFrom, T, U>;

template<typename T, typename U, typename...Rest>
using CommonReference =
concepts::models<concepts::CommonReference, T, U, Rest...>;

template<typename T, typename U, typename...Rest>
using Common =
concepts::models<concepts::Common, T, U, Rest...>;

template<typename T>
using Integral = concepts::models<concepts::Integral, T>;

template<typename T>
using SignedIntegral = concepts::models<concepts::SignedIntegral, T>;

template<typename T>
using UnsignedIntegral = concepts::models<concepts::UnsignedIntegral, T>;

template<typename T>
using Destructible = concepts::models<concepts::Destructible, T>;

template<typename T, typename ...Args>
using Constructible = concepts::models<concepts::Constructible, T, Args...>;

template<typename T>
using DefaultConstructible = concepts::models<concepts::DefaultConstructible, T>;

template<typename T>
using MoveConstructible = concepts::models<concepts::MoveConstructible, T>;

template<typename T>
using CopyConstructible = concepts::models<concepts::CopyConstructible, T>;

template<typename T, typename U>
using Assignable = concepts::models<concepts::Assignable, T, U>;

template<typename T>
using Movable = concepts::models<concepts::Movable, T>;

template<typename T>
using Copyable = concepts::models<concepts::Copyable, T>;

template<typename T, typename U>
using WeaklyEqualityComparable = concepts::models<concepts::WeaklyEqualityComparable, T, U>;

template<typename T, typename U = T>
using EqualityComparable = concepts::models<concepts::EqualityComparable, T, U>;

template<typename T, typename U = T>
using WeaklyOrdered = concepts::models<concepts::WeaklyOrdered, T, U>;

template<typename T, typename U = T>
using TotallyOrdered = concepts::models<concepts::TotallyOrdered, T, U>;

template<typename T>
using SemiRegular = concepts::models<concepts::SemiRegular, T>;

template<typename T>
using Regular = concepts::models<concepts::Regular, T>;

template<typename T, typename U = T>
using Swappable = concepts::models<concepts::Swappable, T, U>;
 */
