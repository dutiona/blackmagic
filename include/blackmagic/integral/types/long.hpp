#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <long L>
struct long_t : std::integral_constant<long, L> {
  using special_tag = tags::long_tag;

  constexpr long_t() = default;

  constexpr long_t(const long_t<L>&) = default;

  long_t<L> operator=(const long_t<L>&)
  {
    return {};
  };

  constexpr long_t(const std::integral_constant<long, L>&)
    : std::integral_constant<long, L>{}
  {
  }

  long_t<L> operator=(const std::integral_constant<long, L>&) const
  {
    return {};
  }

  operator std::integral_constant<long, L>() const
  {
    return {};
  }
};

template <long L>
inline constexpr const auto long_v = _v<long_t<L>>;

} // namespace blackmagic::integral
