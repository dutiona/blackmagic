#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <short S>
struct short_t : std::integral_constant<short, S> {
  using special_tag = tags::short_tag;

  constexpr short_t() = default;

  constexpr short_t(const short_t<S>&) = default;

  short_t<S> operator=(const short_t<S>&)
  {
    return {};
  };

  constexpr short_t(const std::integral_constant<short, S>&)
    : std::integral_constant<short, S>{}
  {
  }

  short_t<S> operator=(const std::integral_constant<short, S>&) const
  {
    return {};
  }

  operator std::integral_constant<short, S>() const
  {
    return {};
  }
};

template <short S>
inline constexpr const auto short_v = _v<short_t<S>>;

} // namespace blackmagic::integral
