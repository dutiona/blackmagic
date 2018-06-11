#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned long UL>
using unsigned_long_t = std::integral_constant<unsigned long, UL>;

template <unsigned long UL>
inline constexpr const auto unsigned_long_v = _v<unsigned_long_t<UL>>;

} // namespace blackmagic::integral
