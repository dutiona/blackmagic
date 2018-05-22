#pragma once

#include "../common/traits_ext.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::integral {

namespace common = blackmagic::common;
using common::_v;

template <bool B>
using bool_t = std::integral_constant<bool, B>;
template <bool B>
inline constexpr const auto bool_v = _v<bool_t<B>>;

using true_t                       = bool_t<true>;
inline constexpr const auto true_v = _v<true_t>;

using false_t                       = bool_t<false>;
inline constexpr const auto false_v = _v<false_t>;

template <char C>
using char_t = std::integral_constant<char, C>;
template <char C>
inline constexpr const auto char_v = _v<char_t<C>>;

template <short S>
using short_t = std::integral_constant<short, S>;
template <short S>
inline constexpr const auto short_v = _v<short_t<S>>;

template <int I>
using int_t = std::integral_constant<int, I>;
template <int I>
inline constexpr const auto int_v = _v<int_t<I>>;

template <long L>
using long_t = std::integral_constant<long, L>;
template <long L>
inline constexpr const auto long_v = _v<long_t<L>>;

template <long long LL>
using long_long_t = std::integral_constant<long long, LL>;
template <long long LL>
inline constexpr const auto long_long_v = _v<long_long_t<LL>>;

template <unsigned char UC>
using unsigned_char_t = std::integral_constant<unsigned, UC>;
template <unsigned char UC>
inline constexpr const auto unsigned_char_v = _v<unsigned_char_t<UC>>;

template <unsigned short US>
using unsigned_short_t = std::integral_constant<unsigned, US>;
template <unsigned short US>
inline constexpr const auto unsigned_short_v = _v<unsigned_short_t<US>>;

template <unsigned U>
using unsigned_t = std::integral_constant<unsigned, U>;
template <unsigned U>
inline constexpr const auto unsigned_v = _v<unsigned_t<U>>;

template <unsigned long UL>
using unsigned_long_t = std::integral_constant<unsigned long, UL>;
template <unsigned long UL>
inline constexpr const auto unsigned_long_v = _v<unsigned_long_t<UL>>;

template <unsigned long long ULL>
using unsigned_long_long_t = std::integral_constant<unsigned long long, ULL>;
template <unsigned long long ULL>
inline constexpr const auto unsigned_long_long_v = _v<unsigned_long_long_t<ULL>>;

template <size_t S>
using size_t_t = std::integral_constant<size_t, S>;
template <size_t S>
inline constexpr const auto size_t_v = _v<size_t_t<S>>;


inline namespace trait {
template <bool B>
inline constexpr const common::value_t<bool_t, B> bool_c{};

inline constexpr const common::basic_value_t<true_t> true_c{};

inline constexpr const common::basic_value_t<false_t> false_c{};

template <char C>
inline constexpr const common::value_t<char_t, C> char_c{};

template <char S>
inline constexpr const common::value_t<short_t, S> short_c{};

template <int I>
inline constexpr const common::value_t<int_t, I> int_c{};

template <long L>
inline constexpr const common::value_t<long_t, L> long_c{};

template <long long LL>
inline constexpr const common::value_t<long_long_t, LL> long_long_c{};

template <unsigned char UC>
inline constexpr const common::value_t<unsigned_char_t, UC> unsigned_char_c{};

template <unsigned short US>
inline constexpr const common::value_t<unsigned_short_t, US> unsigned_short_c{};

template <unsigned U>
inline constexpr const common::value_t<unsigned_t, U> unsigned_c{};

template <unsigned long UL>
inline constexpr const common::value_t<unsigned_long_t, UL> unsigned_long_c{};

template <unsigned long long ULL>
inline constexpr const common::value_t<unsigned_long_long_t, ULL> unsigned_long_long_c{};

template <size_t S>
inline constexpr const common::value_t<size_t_t, S> size_t_c{};

} // namespace trait

} // namespace blackmagic::integral
