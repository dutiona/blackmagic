#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::integral {

template <bool B>
using bool_t = std::integral_constant<bool, B>;
template <bool B>
inline constexpr const bool_t<B> bool_v{};

using true_t = bool_t<true>;
inline constexpr const true_t true_v{};

using false_t = bool_t<false>;
inline constexpr const false_t false_v{};

template <char C>
using char_t = std::integral_constant<char, C>;
template <char C>
inline constexpr const char_t<C> char_v{};

template <int I>
using int_t = std::integral_constant<int, I>;
template <int I>
inline constexpr const int_t<I> int_v{};

template <long L>
using long_t = std::integral_constant<long, L>;
template <long L>
inline constexpr const long_t<L> long_v{};

template <long long LL>
using long_long_t = std::integral_constant<long long, LL>;
template <long long LL>
inline constexpr const long_long_t<LL> long_long_v{};

template <unsigned U>
using unsigned_t = std::integral_constant<unsigned, U>;
template <unsigned U>
inline constexpr const unsigned_t<U> unsigned_v{};

template <unsigned long UL>
using unsigned_long_t = std::integral_constant<unsigned long, UL>;
template <unsigned long UL>
inline constexpr const unsigned_long_t<UL> unsigned_long_v{};

template <unsigned long long ULL>
using unsigned_long_long_t = std::integral_constant<unsigned long long, ULL>;
template <unsigned long long ULL>
inline constexpr const unsigned_long_long_t<ULL> unsigned_long_long_v{};

template <size_t S>
using size_t_ = std::integral_constant<size_t, S>;
template <size_t S>
inline constexpr const size_t_<S> size_t_v{};

} // namespace blackmagic::integral
