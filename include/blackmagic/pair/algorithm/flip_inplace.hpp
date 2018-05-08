#pragma once

#include <utility>

namespace blackmagic::pair { inline namespace algorithm {


// from_tuple
struct flip_inplace_t {
  template <typename T>
  constexpr void operator()(const std::pair<T, T>& p) const
  {
    const auto tmp = p.first;
    p.first        = p.second;
    p.second       = tmp;
  }
};

inline constexpr flip_inplace_t flip_inplace{};


}} // namespace blackmagic::pair::algorithm
