#pragma once

#include "types.hpp"

#include "../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::integral { inline namespace utility {

namespace common = blackmagic::common;
using common::_v;
using common::_v_t;


inline namespace arithmetic {
template <typename T>
using increment_t = std::integral_constant<decltype(_v_t<T> + 1), (_v_t<T> + 1)>;
template <typename T>
inline constexpr const auto increment_v = _v<increment_t<T>>;

template <typename T>
using decrement_t = std::integral_constant<decltype(_v_t<T> - 1), (_v_t<T> - 1)>;
template <typename T>
inline constexpr const auto decrement_v = _v<decrement_t<T>>;

template <typename T, typename U>
using plus_t = std::integral_constant<decltype(_v_t<T> + _v_t<U>), (_v_t<T> + _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto plus_v = _v<plus_t<T, U>>;

template <typename T, typename U>
using minus_t = std::integral_constant<decltype(_v_t<T> - _v_t<U>), (_v_t<T> - _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto minus_v = _v<minus_t<T, U>>;

template <typename T, typename U>
using mult_t = std::integral_constant<decltype(_v_t<T> * _v_t<U>), (_v_t<T> * _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto mult_v = _v<mult_t<T, U>>;

template <typename T, typename U>
using div_t = std::integral_constant<decltype(_v_t<T> / _v_t<U>), (_v_t<T> / _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto div_v = _v<div_t<T, U>>;

template <typename T, typename U>
using mod_t = std::integral_constant<decltype(_v_t<T> % _v_t<U>), _v_t<T> % _v_t<U>>;
template <typename T, typename U>
inline constexpr const auto mod_v = _v<mod_t<T, U>>;

template <typename T>
using positive_t = std::integral_constant<decltype(+_v_t<T>), (+_v_t<T>)>;
template <typename T>
inline constexpr const auto positive_v = _v<positive_t<T>>;

template <typename T>
using negative_t = std::integral_constant<decltype(-_v_t<T>), (-_v_t<T>)>;
template <typename T>
inline constexpr const auto negative_v = _v<negative_t<T>>;

template <typename T>
using bit_not_t = std::integral_constant<decltype(~_v_t<T>), (~_v_t<T>)>;
template <typename T>
inline constexpr const auto bit_not_v = _v<bit_not_t<T>>;

template <typename T, typename U>
using bit_and_t = std::integral_constant<decltype(_v_t<T> & _v_t<U>), (_v_t<T> & _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_and_v = _v<bit_and_t<T, U>>;

template <typename T, typename U>
using bit_or_t = std::integral_constant<decltype(_v_t<T> | _v_t<U>), (_v_t<T> | _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_or_v = _v<bit_or_t<T, U>>;

template <typename T, typename U>
using bit_xor_t = std::integral_constant<decltype(_v_t<T> ^ _v_t<U>), (_v_t<T> ^ _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_xor_v = _v<bit_xor_t<T, U>>;

template <typename T, typename U>
using bit_lshift_t = std::integral_constant<decltype(_v_t<T> << _v_t<U>), (_v_t<T> << _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto bit_lshift_v = _v<bit_lshift_t<T, U>>;

template <typename T, typename U>
// clang-format off
using bit_rshift_t = std::integral_constant<decltype(_v_t<T> >> _v_t<U>), (_v_t<T> >> _v_t<U>)>;
// clang-format on
template <typename T, typename U>
inline constexpr const auto bit_rshift_v = _v<bit_rshift_t<T, U>>;

} // namespace arithmetic


inline namespace comparison {
template <typename T, typename U>
using equal_to_t = bool_t<(_v_t<T> == _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto equal_to_v = _v<equal_to_t<T, U>>;

template <typename T, typename U>
using not_equal_to_t = bool_t<(_v_t<T> != _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto not_equal_to_v = _v<not_equal_to_t<T, U>>;

template <typename T, typename U>
// clang-format off
using greater_than_t = bool_t<(_v_t<T> > _v_t<U>)>;
// clang-format on
template <typename T, typename U>
inline constexpr const auto greater_than_v = _v<greater_than_t<T, U>>;

template <typename T, typename U>
using less_than_t = bool_t<(_v_t<T> < _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto less_than_v = _v<less_than_t<T, U>>;

template <typename T, typename U>
using greater_equal_than_t = bool_t<(_v_t<T> >= _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto greater_equal_than_v = _v<greater_equal_than_t<T, U>>;

template <typename T, typename U>
using less_equal_than_t = bool_t<(_v_t<T> <= _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto less_equal_than_v = _v<less_equal_than_t<T, U>>;

} // namespace comparison


inline namespace logical {
template <typename T, typename U>
using logical_and_t = bool_t<(_v_t<T> && _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto logical_and_v = _v<logical_and_t<T, U>>;

template <typename T, typename U>
using logical_or_t = bool_t<(_v_t<T> || _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto logical_or_v = _v<logical_or_t<T, U>>;

template <typename T>
using logical_not_t = bool_t<(!_v_t<T>)>;
template <typename T>
inline constexpr const auto logical_not_v = _v<logical_not_t<T>>;

} // namespace logical


inline namespace functors {
inline namespace arithmetic {
struct increment_impl {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    return increment_t<T>{};
  }
};
inline constexpr increment_impl increment{};

struct decrement_impl {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    return decrement_t<T>{};
  }
};
inline constexpr const decrement_impl decrement{};

struct plus_impl {
  template <typename T, typename U>
  constexpr plus_t<T, U> operator()(T&&, U&&) const
  {
    return plus_t<T, U>{};
  }
};
inline constexpr const plus_impl plus{};

struct minus_impl {
  template <typename T, typename U>
  constexpr minus_t<T, U> operator()(T&&, U&&) const
  {
    return minus_t<T, U>{};
  }
};
inline constexpr const minus_impl minus{};

struct mult_impl {
  template <typename T, typename U>
  constexpr mult_t<T, U> operator()(T&&, U&&) const
  {
    return mult_t<T, U>{};
  }
};
inline constexpr const mult_impl mult{};

struct div_impl {
  template <typename T, typename U>
  constexpr div_t<T, U> operator()(T&&, U&&) const
  {
    return div_t<T, U>{};
  }
};
inline constexpr const div_impl div{};

struct mod_impl {
  template <typename T, typename U>
  constexpr mod_t<T, U> operator()(T&&, U&&) const
  {
    return mod_t<T, U>{};
  }
};
inline constexpr const mod_impl mod{};

struct positive_impl {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return positive_t<T>{};
  }
};
inline constexpr const positive_impl positive{};

struct negative_impl {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return negative_t<T>{};
  }
};
inline constexpr const negative_impl negative{};

struct bit_not_impl {
  template <typename T>
  constexpr decltype(auto) operator()(T&&) const
  {
    return bit_not_t<T>{};
  }
};
inline constexpr const bit_not_impl bit_not{};

struct bit_and_impl {
  template <typename T, typename U>
  constexpr bit_and_t<T, U> operator()(T&&, U&&) const
  {
    return bit_and_t<T, U>{};
  }
};
inline constexpr const bit_and_impl bit_and{};

struct bit_or_impl {
  template <typename T, typename U>
  constexpr bit_or_t<T, U> operator()(T&&, U&&) const
  {
    return bit_or_t<T, U>{};
  }
};
inline constexpr const bit_or_impl bit_or{};

struct bit_xor_impl {
  template <typename T, typename U>
  constexpr bit_xor_t<T, U> operator()(T&&, U&&) const
  {
    return bit_xor_t<T, U>{};
  }
};
inline constexpr const bit_xor_impl bit_xor{};

struct bit_lshift_impl {
  template <typename T, typename U>
  constexpr bit_lshift_t<T, U> operator()(T&&, U&&) const
  {
    return bit_lshift_t<T, U>{};
  }
};
inline constexpr const bit_lshift_impl bit_lshift{};

struct bit_rshift_impl {
  template <typename T, typename U>
  constexpr bit_rshift_t<T, U> operator()(T&&, U&&) const
  {
    return bit_rshift_t<T, U>{};
  }
};
inline constexpr const bit_rshift_impl bit_rshift{};

} // namespace arithmetic


inline namespace comparison {
struct equal_to_impl {
  template <typename T, typename U>
  constexpr equal_to_t<T, U> operator()(T&&, U&&) const
  {
    return equal_to_t<T, U>{};
  }
};
inline constexpr const equal_to_impl equal_to{};

struct not_equal_to_impl {
  template <typename T, typename U>
  constexpr not_equal_to_t<T, U> operator()(T&&, U&&) const
  {
    return not_equal_to_t<T, U>{};
  }
};
inline constexpr const not_equal_to_impl not_equal_to{};

struct greater_than_impl {
  template <typename T, typename U>
  constexpr greater_than_t<T, U> operator()(T&&, U&&) const
  {
    return greater_than_t<T, U>{};
  }
};
inline constexpr const greater_than_impl greater_than{};

struct less_than_impl {
  template <typename T, typename U>
  constexpr less_than_t<T, U> operator()(T&&, U&&) const
  {
    return less_than_t<T, U>{};
  }
};
inline constexpr const less_than_impl less_than{};

struct greater_equal_than_impl {
  template <typename T, typename U>
  constexpr greater_equal_than_t<T, U> operator()(T&&, U&&) const
  {
    return greater_equal_than_t<T, U>{};
  }
};
inline constexpr const greater_equal_than_impl greater_equal_than{};

struct less_equal_than_impl {
  template <typename T, typename U>
  constexpr less_equal_than_t<T, U> operator()(T&&, U&&) const
  {
    return less_equal_than_t<T, U>{};
  }
};
inline constexpr const less_equal_than_impl less_equal_than{};
} // namespace comparison


inline namespace logical {
struct logical_and_impl {
  template <typename T, typename U>
  constexpr logical_and_t<T, U> operator()(T&&, U&&) const
  {
    return logical_and_t<T, U>{};
  }
};
inline constexpr const logical_and_impl logical_and{};

struct logical_or_impl {
  template <typename T, typename U>
  constexpr logical_or_t<T, U> operator()(T&&, U&&) const
  {
    return logical_or_t<T, U>{};
  }
};
inline constexpr const logical_or_impl logical_or{};

struct logical_not_impl {
  template <typename T>
  constexpr logical_not_t<T> operator()(T&&) const
  {
    return logical_not_t<T>{};
  }
};
inline constexpr const logical_not_impl logical_not{};
} // namespace logical

} // namespace functors

}} // namespace blackmagic::integral::utility
