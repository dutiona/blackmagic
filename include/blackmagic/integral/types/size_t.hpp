#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <size_t S>
using size_t_t = std::integral_constant<size_t, S>;

template <size_t S>
inline constexpr const auto size_t_v = _v<size_t_t<S>>;

} // namespace blackmagic::integral
