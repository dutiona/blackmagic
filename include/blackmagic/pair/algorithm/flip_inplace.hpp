#pragma once

#include "../../common/traits_ext.hpp"

#include <algorithm>
#include <utility>

namespace blackmagic::pair { inline namespace algorithm {

namespace common = blackmagic::common;

// from_tuple
struct flip_inplace_t {
  template <typename T, typename U>
  constexpr void operator()(std::pair<T, U>& p) const
  {
    static_assert(common::is_swappable_with_v<T, U>, "<First> and <Second> are not swappable!");

    using std::swap;
    swap(std::move(p.first), std::move(p.second));
  }
};

inline constexpr const flip_inplace_t flip_inplace{};

}} // namespace blackmagic::pair::algorithm
