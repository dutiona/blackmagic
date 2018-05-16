#pragma once

#include <utility>

namespace blackmagic::pair { inline namespace algorithm {


// from_tuple
struct flip_t {
  template <typename Pair>
  constexpr auto operator()(Pair&& p) const
  {
    return std::make_pair(std::forward<Pair>(p).second, std::forward<Pair>(p).first);
  }
};

inline constexpr const flip_t flip{};


}} // namespace blackmagic::pair::algorithm
