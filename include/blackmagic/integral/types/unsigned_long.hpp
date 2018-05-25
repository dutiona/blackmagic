#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned long UL>
struct unsigned_long_t : std::integral_constant<unsigned long, UL> {
  using special_tag = tags::unsigned_long_tag;

  constexpr unsigned_long_t() = default;

  constexpr unsigned_long_t(const unsigned_long_t<UL>&) = default;

  unsigned_long_t<UL> operator=(const unsigned_long_t<UL>&)
  {
    return {};
  };

  constexpr unsigned_long_t(const std::integral_constant<unsigned long, UL>&)
    : std::integral_constant<unsigned long, UL>{}
  {
  }

  unsigned_long_t<UL> operator=(const std::integral_constant<unsigned long, UL>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned long, UL>() const
  {
    return {};
  }
};

template <unsigned long UL>
inline constexpr const auto unsigned_long_v = _v<unsigned_long_t<UL>>;

} // namespace blackmagic::integral
