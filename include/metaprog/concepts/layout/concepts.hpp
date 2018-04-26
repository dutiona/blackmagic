#pragma once

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

#include "../engine.hpp"
#include "traits.hpp"

#include <string_view>

namespace metaprog::concepts { inline namespace layout {

using namespace std::literals;
namespace traits = metaprog::traits;

// trivially copyable
inline constexpr auto TriviallyCopyable = is_true<traits::is_trivially_copyable>("TriviallyCopyable"sv);

// trivial
inline constexpr auto Trivial = is_true<traits::is_trivial>("Trivial"sv);

// standard layout
inline constexpr auto StandardLayout = is_true<traits::is_standard_layout>("StandardLayout"sv);

}} // namespace metaprog::concepts::layout
