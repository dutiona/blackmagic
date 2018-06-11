#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned long long ULL>
using unsigned_long_long_t = std::integral_constant<unsigned long long, ULL>;

template <unsigned long long ULL>
inline constexpr const auto unsigned_long_long_v = _v<unsigned_long_long_t<ULL>>;

} // namespace blackmagic::integral
