#pragma once

#include <utility>

namespace blackmagic::pair { inline namespace algorithm {


// from_tuple
struct flip_t {
  template <typename T, typename U>
  constexpr auto operator()(const std::pair<T, U>& p) const
  {
    return std::make_pair(p.second, p.first);
  }
};

inline constexpr const flip_t flip{};


}} // namespace blackmagic::pair::algorithm
