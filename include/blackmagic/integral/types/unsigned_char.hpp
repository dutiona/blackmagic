#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned char UC>
struct unsigned_char_t : std::integral_constant<unsigned char, UC> {
  using special_tag = tags::unsigned_char_tag;

  constexpr unsigned_char_t() = default;

  constexpr unsigned_char_t(const unsigned_char_t<UC>&) = default;

  unsigned_char_t<UC> operator=(const unsigned_char_t<UC>&)
  {
    return {};
  };

  constexpr unsigned_char_t(const std::integral_constant<unsigned char, UC>&)
    : std::integral_constant<unsigned char, UC>{}
  {
  }

  unsigned_char_t<UC> operator=(const std::integral_constant<unsigned char, UC>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned char, UC>() const
  {
    return {};
  }
};

template <unsigned char UC>
inline constexpr const auto unsigned_char_v = _v<unsigned_char_t<UC>>;

} // namespace blackmagic::integral
