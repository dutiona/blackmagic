#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned short US>
struct unsigned_short_t : std::integral_constant<unsigned short, US> {
  using special_tag = tags::unsigned_short_tag;

  constexpr unsigned_short_t() = default;

  constexpr unsigned_short_t(const unsigned_short_t<US>&) = default;

  unsigned_short_t<US> operator=(const unsigned_short_t<US>&)
  {
    return {};
  };

  constexpr unsigned_short_t(const std::integral_constant<unsigned short, US>&)
    : std::integral_constant<unsigned short, US>{}
  {
  }

  unsigned_short_t<US> operator=(const std::integral_constant<unsigned short, US>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned short, US>() const
  {
    return {};
  }
};

template <unsigned short US>
inline constexpr const auto unsigned_short_v = _v<unsigned_short_t<US>>;

} // namespace blackmagic::integral
