#pragma once

#include "../../../common/common.hpp"

#include <array>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common = blackmagic::common;

namespace details {

template <bool... bools>
struct filter_indexes {
  static constexpr auto make_indexes()
  {
    constexpr bool             b[] = {bools..., false};
    constexpr std::size_t      N   = common::count<bools..., false>::value;
    std::array<std::size_t, N> indexes{};
    auto                       keep = indexes.begin();
    for (size_t i = 0; i < sizeof...(bools); ++i)
      if (b[i])
        *keep++ = i;
    return indexes;
  }
  static constexpr auto indexes = make_indexes();
};

} // namespace details

}} // namespace blackmagic::tuple::algorithm