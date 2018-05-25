#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned long long ULL>
struct unsigned_long_long_t : std::integral_constant<unsigned long long, ULL> {
  using special_tag = tags::unsigned_long_long_tag;

  constexpr unsigned_long_long_t() = default;

  constexpr unsigned_long_long_t(const unsigned_long_long_t<ULL>&) = default;

  unsigned_long_long_t<ULL> operator=(const unsigned_long_long_t<ULL>&)
  {
    return {};
  };

  constexpr unsigned_long_long_t(const std::integral_constant<unsigned long long, ULL>&)
    : std::integral_constant<unsigned long long, ULL>{}
  {
  }

  unsigned_long_long_t<ULL> operator=(const std::integral_constant<unsigned long long, ULL>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned long long, ULL>() const
  {
    return {};
  }
};

template <unsigned long long ULL>
inline constexpr const auto unsigned_long_long_v = _v<unsigned_long_long_t<ULL>>;

} // namespace blackmagic::integral
