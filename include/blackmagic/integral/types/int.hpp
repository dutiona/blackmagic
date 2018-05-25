#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <int I>
struct int_t : std::integral_constant<int, I> {
  using special_tag = tags::int_tag;

  constexpr int_t() = default;

  constexpr int_t(const int_t<I>&) = default;

  int_t<I> operator=(const int_t<I>&)
  {
    return {};
  };

  constexpr int_t(const std::integral_constant<int, I>&)
    : std::integral_constant<int, I>{}
  {
  }

  int_t<I> operator=(const std::integral_constant<int, I>&) const
  {
    return {};
  }

  operator std::integral_constant<int, I>() const
  {
    return {};
  }
};

template <int I>
inline constexpr const auto int_v = _v<int_t<I>>;

} // namespace blackmagic::integral
