#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <long long LL>
struct long_long_t : std::integral_constant<long long, LL> {
  using special_tag = tags::long_long_tag;

  constexpr long_long_t() = default;

  constexpr long_long_t(const long_long_t<LL>&) = default;

  long_long_t<LL> operator=(const long_long_t<LL>&)
  {
    return {};
  };

  constexpr long_long_t(const std::integral_constant<long long, LL>&)
    : std::integral_constant<long long, LL>{}
  {
  }

  long_long_t<LL> operator=(const std::integral_constant<long long, LL>&) const
  {
    return {};
  }

  operator std::integral_constant<long long, LL>() const
  {
    return {};
  }
};

template <long long LL>
inline constexpr const auto long_long_v = _v<long_long_t<LL>>;

} // namespace blackmagic::integral
