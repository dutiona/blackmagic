#pragma once

#include "../../../common/traits_ext.hpp"
#include "../../../type/algorithm/count.hpp"

#include <array>

namespace blackmagic::tuple { inline namespace algorithm {

namespace type   = blackmagic::type;

namespace details {

template <bool... bools>
struct filter_indexes {
  static constexpr auto make_indexes()
  {
    using blackmagic::common::_v;

    constexpr bool             b[] = {bools..., false};
    constexpr std::size_t      N   = _v<type::count<bools..., false>>;
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
