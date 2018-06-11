#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned U>
using unsigned_t = std::integral_constant<unsigned, U>;

template <unsigned U>
inline constexpr const auto unsigned_v = _v<unsigned_t<U>>;

} // namespace blackmagic::integral
