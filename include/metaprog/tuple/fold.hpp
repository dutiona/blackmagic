#pragma once

#include "fold_left.hpp"

namespace metaprog::tuple { inline namespace algorithm {

using fold_t = fold_left_t;

inline constexpr fold_t fold{};

}} // namespace metaprog::tuple::algorithm
