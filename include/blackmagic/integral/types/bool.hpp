#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <bool B>
using bool_t = std::integral_constant<bool, B>;

template <bool B>
inline constexpr const auto bool_v = _v<bool_t<B>>;

using true_t                       = bool_t<true>;
inline constexpr const auto true_v = _v<true_t>;

using false_t                       = bool_t<false>;
inline constexpr const auto false_v = _v<false_t>;

} // namespace blackmagic::integral
