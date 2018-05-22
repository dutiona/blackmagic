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
using incr_t = std::integral_constant<decltype(_v_t<T> + 1), (_v_t<T> + 1)>;
template <typename T>
inline constexpr const auto incr_v = _v<incr_t<T>>;

template <typename T>
using decr_t = std::integral_constant<decltype(_v_t<T> - 1), (_v_t<T> - 1)>;
template <typename T>
inline constexpr const auto decr_v = _v<decr_t<T>>;

template <typename T, typename U>
using binary_plus_t = std::integral_constant<decltype(_v_t<T> + _v_t<U>), (_v_t<T> + _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto binary_plus_v = _v<binary_plus_t<T, U>>;

template <typename T, typename U>
using binary_minus_t = std::integral_constant<decltype(_v_t<T> - _v_t<U>), (_v_t<T> - _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto binary_minus_v = _v<binary_minus_t<T, U>>;

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
using unary_plus_t = std::integral_constant<decltype(+_v_t<T>), (+_v_t<T>)>;
template <typename T>
inline constexpr const auto unary_plus_v = _v<unary_plus_t<T>>;

template <typename T>
using unary_minus_t = std::integral_constant<decltype(-_v_t<T>), (-_v_t<T>)>;
template <typename T>
inline constexpr const auto unary_minus_v = _v<unary_minus_t<T>>;

template <typename T>
using not_t = std::integral_constant<decltype(~_v_t<T>), (~_v_t<T>)>;
template <typename T>
inline constexpr const auto not_v = _v<not_t<T>>;

template <typename T, typename U>
using and_t = std::integral_constant<decltype(_v_t<T> & _v_t<U>), (_v_t<T> & _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto and_v = _v<and_t<T, U>>;

template <typename T, typename U>
using or_t = std::integral_constant<decltype(_v_t<T> | _v_t<U>), (_v_t<T> | _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto or_v = _v<or_t<T, U>>;

template <typename T, typename U>
using xor_t = std::integral_constant<decltype(_v_t<T> ^ _v_t<U>), (_v_t<T> ^ _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto xor_v = _v<xor_t<T, U>>;

template <typename T, typename U>
using lshift_t = std::integral_constant<decltype(_v_t<T> << _v_t<U>), (_v_t<T> << _v_t<U>)>;
template <typename T, typename U>
inline constexpr const auto lshift_v = _v<lshift_t<T, U>>;

template <typename T, typename U>
// clang-format off
using rshift_t = std::integral_constant<decltype(_v_t<T> >> _v_t<U>), (_v_t<T> >> _v_t<U>)>;
// clang-format on
template <typename T, typename U>
inline constexpr const auto rshift_v = _v<rshift_t<T, U>>;

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


inline namespace traits {
inline namespace arithmetic {
template <typename T>
inline constexpr const common::trait_t<incr_t, T> incr{};

template <typename T>
inline constexpr const common::trait_t<decr_t, T> decr{};

template <typename T, typename U>
inline constexpr const common::trait_t<binary_plus_t, T, U> binary_plus{};

template <typename T, typename U>
inline constexpr const common::trait_t<binary_minus_t, T, U> binary_minus{};

template <typename T, typename U>
inline constexpr const common::trait_t<mult_t, T, U> mult{};

template <typename T, typename U>
inline constexpr const common::trait_t<div_t, T, U> div{};

template <typename T, typename U>
inline constexpr const common::trait_t<mod_t, T, U> mod{};

template <typename T>
inline constexpr const common::trait_t<unary_plus_t, T> unary_plus{};

template <typename T>
inline constexpr const common::trait_t<unary_minus_t, T> unary_minus{};

template <typename T>
inline constexpr const common::trait_t<not_t, T> Not{};

template <typename T, typename U>
inline constexpr const common::trait_t<and_t, T, U> And{};

template <typename T, typename U>
inline constexpr const common::trait_t<or_t, T, U> Or{};

template <typename T, typename U>
inline constexpr const common::trait_t<xor_t, T, U> Xor{};

template <typename T, typename U>
inline constexpr const common::trait_t<lshift_t, T, U> lshift{};

template <typename T, typename U>
inline constexpr const common::trait_t<rshift_t, T, U> rshift{};

} // namespace arithmetic


inline namespace comparison {
template <typename T, typename U>
inline constexpr const common::trait_t<equal_to_t, T, U> equal_to{};

template <typename T, typename U>
inline constexpr const common::trait_t<not_equal_to_t, T, U> not_equal_to{};

template <typename T, typename U>
inline constexpr const common::trait_t<greater_than_t, T, U> greater_than{};

template <typename T, typename U>
inline constexpr const common::trait_t<less_than_t, T, U> less_than{};

template <typename T, typename U>
inline constexpr const common::trait_t<greater_equal_than_t, T, U> greater_equal_than{};

template <typename T, typename U>
inline constexpr const common::trait_t<less_equal_than_t, T, U> less_equal_than{};
} // namespace comparison


inline namespace logical {
template <typename T, typename U>
inline constexpr const common::trait_t<logical_and_t, T, U> logical_and{};

template <typename T, typename U>
inline constexpr const common::trait_t<logical_or_t, T, U> logical_or{};

template <typename T>
inline constexpr const common::trait_t<logical_not_t, T> logical_not{};
} // namespace logical

} // namespace traits

}} // namespace blackmagic::integral::utility
