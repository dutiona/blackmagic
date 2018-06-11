#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <long L>
using long_t = std::integral_constant<long, L>;

template <long L>
inline constexpr const auto long_v = _v<long_t<L>>;

} // namespace blackmagic::integral
