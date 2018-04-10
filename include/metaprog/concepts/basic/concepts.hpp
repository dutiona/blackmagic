#pragma once

#include "details/concepts_impl.hpp"

#include "../engine.hpp"

#include <string_view>

namespace metaprog::concepts { inline namespace basic {

using namespace std::literals;

// default constructible
inline constexpr auto DefaultConstructible =
  make_concept_item_from_predicate<details::default_constructible_impl>("DefaultConstructible"sv);

// move constructible
inline constexpr auto MoveConstructible =
  make_concept_item_from_predicate<details::move_constructible_impl>("MoveConstructible"sv);

// copy constructible
inline constexpr auto CopyConstructible =
  make_concept_item_from_predicate<details::copy_constructible_impl>("CopyConstructible"sv);

// move assignable
inline constexpr auto MoveAssignable =
  make_concept_item_from_predicate<details::move_assignable_impl>("MoveAssignable"sv);

// copy assignable
inline constexpr auto CopyAssignable =
  make_concept_item_from_predicate<details::copy_assignable_impl>("CopyAssignable"sv);

// destructible
inline constexpr auto Destructible = make_concept_item_from_predicate<details::destructible_impl>("Destructible"sv);

}} // namespace concepts::concepts::basic
