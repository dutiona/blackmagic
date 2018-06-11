#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned short US>
using unsigned_short_t = std::integral_constant<unsigned short, US>;

template <unsigned short US>
inline constexpr const auto unsigned_short_v = _v<unsigned_short_t<US>>;

} // namespace blackmagic::integral
