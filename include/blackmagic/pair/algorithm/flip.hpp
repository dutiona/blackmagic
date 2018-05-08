#pragma once

#include <utility>

namespace blackmagic::pair { inline namespace algorithm {


// from_tuple
struct flip_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(const std::pair<T, U>& p) const
  {
    return std::make_pair(p.second, p.first);
  }
};

inline constexpr flip_t flip{};


}} // namespace blackmagic::pair::algorithm
