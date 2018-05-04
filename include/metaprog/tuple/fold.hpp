#pragma once

#include "fold_left.hpp"

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

using fold_t = fold_left_t;

} // namespace details

inline constexpr details::fold_t fold{};

}} // namespace metaprog::tuple::algorithm
