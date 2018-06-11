#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <long long LL>
using long_long_t = std::integral_constant<long long, LL>;

template <long long LL>
inline constexpr const auto long_long_v = _v<long_long_t<LL>>;

} // namespace blackmagic::integral
