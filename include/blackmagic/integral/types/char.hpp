#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <char C>
using char_t = std::integral_constant<char, C>;

template <char C>
inline constexpr const auto char_v = _v<char_t<C>>;

} // namespace blackmagic::integral
