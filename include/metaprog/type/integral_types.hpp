#pragma once

#include <cstddef>
#include <type_traits>

namespace metaprog::type {

template <bool b>
using bool_ = std::integral_constant<bool, b>;

template <bool c>
using char_ = std::integral_constant<char, c>;

template <int i>
using int_ = std::integral_constant<int, i>;

template <long l>
using long_ = std::integral_constant<long, l>;

template <long long ll>
using long_long_ = std::integral_constant<long long, ll>;

template <unsigned u>
using unsigned_ = std::integral_constant<unsigned, u>;

template <unsigned long ul>
using unsigned_long_ = std::integral_constant<unsigned long, ul>;

template <unsigned long long ull>
using unsigned_long_long_ = std::integral_constant<unsigned long long, ull>;

template <size_t s>
using size_t_ = std::integral_constant<size_t, s>;

} // namespace metaprog::type
