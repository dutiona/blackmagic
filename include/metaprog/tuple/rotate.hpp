#pragma once

#include "rotate_left.hpp"

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

using rorate_t = rotate_left_t;

} // namespace details

inline constexpr details::rorate_t rorate{};

}} // namespace metaprog::tuple::algorithm
