#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned int UI>
struct unsigned_int_t : std::integral_constant<unsigned int, UI> {
  using special_tag = tags::unsigned_int_tag;

  constexpr unsigned_int_t() = default;

  constexpr unsigned_int_t(const unsigned_int_t<UI>&) = default;

  unsigned_int_t<UI> operator=(const unsigned_int_t<UI>&)
  {
    return {};
  };

  constexpr unsigned_int_t(const std::integral_constant<unsigned int, UI>&)
    : std::integral_constant<unsigned int, UI>{}
  {
  }

  unsigned_int_t<UI> operator=(const std::integral_constant<unsigned int, UI>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned int, UI>() const
  {
    return {};
  }
};

template <unsigned int UI>
inline constexpr const auto unsigned_int_v = _v<unsigned_int_t<UI>>;

} // namespace blackmagic::integral
