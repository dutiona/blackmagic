#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned int UI>
using unsigned_int_t = std::integral_constant<unsigned int, UI>;

template <unsigned int UI>
inline constexpr const auto unsigned_int_v = _v<unsigned_int_t<UI>>;

} // namespace blackmagic::integral
