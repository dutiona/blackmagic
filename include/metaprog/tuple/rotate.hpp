#pragma once

#include "rotate_left.hpp"

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

using rotate_t = rotate_left_t;

} // namespace details

inline constexpr details::rotate_t rotate{};

}} // namespace metaprog::tuple::algorithm
