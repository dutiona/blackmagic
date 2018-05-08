#pragma once

#include "traits.hpp"
#include "../engine.hpp"

#include <string_view>

namespace blackmagic::concepts { inline namespace basic {

using namespace std::literals;
namespace traits = blackmagic::traits;

// default constructible
inline constexpr auto DefaultConstructible = is_true<traits::is_default_constructible>("DefaultConstructible"sv);

// move constructible
inline constexpr auto MoveConstructible = is_true<traits::is_move_constructible>("MoveConstructible"sv);

// copy constructible
inline constexpr auto CopyConstructible = is_true<traits::is_copy_constructible>("CopyConstructible"sv);

// move assignable
inline constexpr auto MoveAssignable = is_true<traits::is_move_assignable>("MoveAssignable"sv);

// copy assignable
inline constexpr auto CopyAssignable = is_true<traits::is_copy_assignable>("CopyAssignable"sv);

// destructible
inline constexpr auto Destructible = is_true<traits::is_destructible>("Destructible"sv);

}} // namespace blackmagic::concepts::basic
