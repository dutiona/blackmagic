#pragma once

#include <type_traits>

namespace blackmagic::traits { inline namespace layout {

// trivially copyable
template <typename T>
using is_trivially_copyable = std::is_trivially_copyable<T>;
template <typename T>
using is_trivially_copyable_t = typename is_trivially_copyable<T>::type;
template <typename T>
constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;

// trivial
template <typename T>
using is_trivial = std::is_trivial<T>;
template <typename T>
using is_trivial_t = typename is_trivial<T>::type;
template <typename T>
constexpr bool is_trivial_v = is_trivial<T>::value;

// standard layout
template <typename T>
using is_standard_layout = std::is_standard_layout<T>;
template <typename T>
using is_standard_layout_t = typename is_standard_layout<T>::type;
template <typename T>
constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

}} // namespace blackmagic::traits::layout
