#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::traits { inline namespace layout {

using common::_t;
using common::_v;

// trivially copyable
template <typename T>
using is_trivially_copyable = std::is_trivially_copyable<T>;
template <typename T>
using is_trivially_copyable_t = _t<is_trivially_copyable<T>>;
template <typename T>
constexpr bool is_trivially_copyable_v = _v<is_trivially_copyable<T>>;

// trivial
template <typename T>
using is_trivial = std::is_trivial<T>;
template <typename T>
using is_trivial_t = _t<is_trivial<T>>;
template <typename T>
constexpr bool is_trivial_v = _v<is_trivial<T>>;

// standard layout
template <typename T>
using is_standard_layout = std::is_standard_layout<T>;
template <typename T>
using is_standard_layout_t = _t<is_standard_layout<T>>;
template <typename T>
constexpr bool is_standard_layout_v = _v<is_standard_layout<T>>;

}} // namespace blackmagic::traits::layout
