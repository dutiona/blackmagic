#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned char UC>
using unsigned_char_t = std::integral_constant<unsigned char, UC>;

template <unsigned char UC>
inline constexpr const auto unsigned_char_v = _v<unsigned_char_t<UC>>;

} // namespace blackmagic::integral
