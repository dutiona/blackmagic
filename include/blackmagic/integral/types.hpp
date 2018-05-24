#pragma once

#include "../common/traits_ext.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::integral {

namespace common = blackmagic::common;
using common::_v;

template <bool B>
struct bool_t : std::integral_constant<bool, B> {
};
template <bool B>
inline constexpr const auto bool_v = _v<bool_t<B>>;

using true_t                       = bool_t<true>;
inline constexpr const auto true_v = _v<true_t>;

using false_t                       = bool_t<false>;
inline constexpr const auto false_v = _v<false_t>;

template <char C>
struct char_t : std::integral_constant<char, C> {
};
template <char C>
inline constexpr const auto char_v = _v<char_t<C>>;

template <short S>
struct short_t : std::integral_constant<short, S> {
};
template <short S>
inline constexpr const auto short_v = _v<short_t<S>>;

template <int I>
struct int_t : std::integral_constant<int, I> {
};
template <int I>
inline constexpr const auto int_v = _v<int_t<I>>;

template <long L>
struct long_t : std::integral_constant<long, L> {
};
template <long L>
inline constexpr const auto long_v = _v<long_t<L>>;

template <long long LL>
struct long_long_t : std::integral_constant<long long, LL> {
};
template <long long LL>
inline constexpr const auto long_long_v = _v<long_long_t<LL>>;

template <unsigned char UC>
struct unsigned_char_t : std::integral_constant<unsigned char, UC> {
};
template <unsigned char UC>
inline constexpr const auto unsigned_char_v = _v<unsigned_char_t<UC>>;

template <unsigned short US>
struct unsigned_short_t : std::integral_constant<unsigned short, US> {
};
template <unsigned short US>
inline constexpr const auto unsigned_short_v = _v<unsigned_short_t<US>>;

template <unsigned U>
struct unsigned_t : std::integral_constant<unsigned, U> {
};
template <unsigned U>
inline constexpr const auto unsigned_v = _v<unsigned_t<U>>;

template <unsigned int UI>
struct unsigned_int_t : std::integral_constant<unsigned int, UI> {
};
template <unsigned int UI>
inline constexpr const auto unsigned_int_v = _v<unsigned_int_t<UI>>;

template <unsigned long UL>
struct unsigned_long_t : std::integral_constant<unsigned long, UL> {
};
template <unsigned long UL>
inline constexpr const auto unsigned_long_v = _v<unsigned_long_t<UL>>;

template <unsigned long long ULL>
struct unsigned_long_long_t : std::integral_constant<unsigned long long, ULL> {
};
template <unsigned long long ULL>
inline constexpr const auto unsigned_long_long_v = _v<unsigned_long_long_t<ULL>>;

template <size_t S>
struct size_t_t : std::integral_constant<size_t, S> {
};
template <size_t S>
inline constexpr const auto size_t_v = _v<size_t_t<S>>;

} // namespace blackmagic::integral
