#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <short S>
using short_t = std::integral_constant<short, S>;

template <short S>
inline constexpr const auto short_v = _v<short_t<S>>;

} // namespace blackmagic::integral
