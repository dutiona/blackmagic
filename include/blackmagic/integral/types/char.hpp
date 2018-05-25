#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <char C>
struct char_t : std::integral_constant<char, C> {
  using special_tag = tags::char_tag;

  constexpr char_t() = default;

  constexpr char_t(const char_t<C>&) = default;

  char_t<C> operator=(const char_t<C>&)
  {
    return {};
  };

  constexpr char_t(const std::integral_constant<char, C>&)
    : std::integral_constant<char, C>{}
  {
  }

  char_t<C> operator=(const std::integral_constant<char, C>&) const
  {
    return {};
  }

  operator std::integral_constant<char, C>() const
  {
    return {};
  }
};

template <char C>
inline constexpr const auto char_v = _v<char_t<C>>;

} // namespace blackmagic::integral
