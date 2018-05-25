#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <unsigned U>
struct unsigned_t : std::integral_constant<unsigned, U> {
  using special_tag = tags::unsigned_tag;

  constexpr unsigned_t() = default;

  constexpr unsigned_t(const unsigned_t<U>&) = default;

  unsigned_t<U> operator=(const unsigned_t<U>&)
  {
    return {};
  };

  constexpr unsigned_t(const std::integral_constant<unsigned, U>&)
    : std::integral_constant<unsigned, U>{}
  {
  }

  unsigned_t<U> operator=(const std::integral_constant<unsigned, U>&) const
  {
    return {};
  }

  operator std::integral_constant<unsigned, U>() const
  {
    return {};
  }
};

template <unsigned U>
inline constexpr const auto unsigned_v = _v<unsigned_t<U>>;

} // namespace blackmagic::integral
