#pragma once

#include "../tags.hpp"

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral {

using common::_v;

template<bool B>
struct bool_t : std::integral_constant<bool, B> {
  using special_tag = tags::bool_tag;

  constexpr bool_t() = default;

  constexpr bool_t(const bool_t<B> &) = default;

  bool_t<B> operator=(const bool_t<B> &) {
    return {};
  };

  constexpr bool_t(const std::integral_constant<bool, B> &)
    : std::integral_constant<bool, B>{} {
  }

  bool_t<B> operator=(const std::integral_constant<bool, B> &) const {
    return {};
  }

  operator std::integral_constant<bool, B>() const {
    return {};
  }
};

template<bool B>
inline constexpr const auto bool_v = _v<bool_t<B>>;

using true_t                       = bool_t<true>;
inline constexpr const auto true_v = _v<true_t>;

using false_t                       = bool_t<false>;
inline constexpr const auto false_v = _v<false_t>;

}
