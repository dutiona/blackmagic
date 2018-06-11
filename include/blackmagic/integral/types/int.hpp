#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <int I>
using int_t = std::integral_constant<int, I>;

template <int I>
inline constexpr const auto int_v = _v<int_t<I>>;

} // namespace blackmagic::integral
