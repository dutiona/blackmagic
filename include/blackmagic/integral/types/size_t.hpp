#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template <size_t S>
struct size_t_t : std::integral_constant<size_t, S> {
  using special_tag = tags::size_t_tag;

  constexpr size_t_t() = default;

  constexpr size_t_t(const size_t_t<S>&) = default;

  size_t_t<S> operator=(const size_t_t<S>&)
  {
    return {};
  };

  constexpr size_t_t(const std::integral_constant<size_t, S>&)
    : std::integral_constant<size_t, S>{}
  {
  }

  size_t_t<S> operator=(const std::integral_constant<size_t, S>&) const
  {
    return {};
  }

  operator std::integral_constant<size_t, S>() const
  {
    return {};
  }
};

template <size_t S>
inline constexpr const auto size_t_v = _v<size_t_t<S>>;

} // namespace blackmagic::integral
