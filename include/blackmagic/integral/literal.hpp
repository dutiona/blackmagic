#pragma once

#include "types.hpp"

#include <cstddef>
#include <string_view>

namespace blackmagic::integral::literals {

namespace details {

// part of this code is taken from boost::hana

constexpr int to_int(char c)
{
  int result = 0;

  if (c >= 'A' && c <= 'F') {
    result = static_cast<int>(c) - static_cast<int>('A') + 10;
  }
  else if (c >= 'a' && c <= 'f') {
    result = static_cast<int>(c) - static_cast<int>('a') + 10;
  }
  else {
    result = static_cast<int>(c) - static_cast<int>('0');
  }

  return result;
}

template <std::size_t N>
constexpr long long parse_signed_number(const char (&arr)[N])
{
  long long   base   = 10;
  std::size_t offset = 0;

  if (N > 2) {
    bool starts_with_zero = arr[0] == '0';
    bool is_hex           = starts_with_zero && arr[1] == 'x';
    bool is_binary        = starts_with_zero && arr[1] == 'b';

    if (is_hex) {
      // 0xDEADBEEF (hexadecimal)
      base   = 16;
      offset = 2;
    }
    else if (is_binary) {
      // 0b101011101 (binary)
      base   = 2;
      offset = 2;
    }
    else if (starts_with_zero) {
      // 012345 (octal)
      base   = 8;
      offset = 1;
    }
  }

  long long number     = 0;
  long long multiplier = 1;

  for (std::size_t i = 0; i < N - offset; ++i) {
    char c = arr[N - 1 - i];
    if (c != '\'') { // skip digit separators
      number += to_int(c) * multiplier;
      multiplier *= base;
    }
  }

  return number;
}

template <std::size_t N>
constexpr unsigned long long parse_unsigned_number(const char (&arr)[N])
{
  const auto number = parse_signed_number(arr);

  if (number < 0) {
    throw "Number must be positive!";
  }
  else {
    return static_cast<unsigned long long>(number);
  }
}

template <std::size_t N>
constexpr bool parse_bool(const char (&arr)[N])
{
  return static_cast<bool>(parse_signed_number(arr));
}

template <std::size_t N>
constexpr char parse_char(const char (&arr)[N])
{
  static_assert(N == 1, "Only a single char is tolerated!");

  return arr[0];
}

} // namespace details

template <char... C>
constexpr decltype(auto) operator""_c()
{
  return long_long_v<details::parse_signed_number({C...})>;
}

template <char... C>
constexpr decltype(auto) operator""_bc()
{
  return bool_v<details::parse_bool({C...})>;
}

template <char... C>
constexpr decltype(auto) operator""_cc()
{
  return char_v<details::parse_char({C...})>;
}

template <char... C>
constexpr decltype(auto) operator""_sc()
{
  return short_v<static_cast<short>(details::parse_signed_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_ic()
{
  return int_v<static_cast<int>(details::parse_signed_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_lc()
{
  return long_v<static_cast<long>(details::parse_signed_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_llc()
{
  return long_long_v<details::parse_signed_number({C...})>;
}

template <char... C>
constexpr decltype(auto) operator""_ucc()
{
  return unsigned_char_v<static_cast<unsigned char>(details::parse_unsigned_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_usc()
{
  return unsigned_short_v<static_cast<unsigned short>(details::parse_unsigned_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_uc()
{
  return unsigned_long_long_v<details::parse_unsigned_number({C...})>;
}

template <char... C>
constexpr decltype(auto) operator""_uic()
{
  return unsigned_v<static_cast<unsigned>(details::parse_unsigned_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_ulc()
{
  return unsigned_long_v<static_cast<unsigned long>(details::parse_unsigned_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_ullc()
{
  return unsigned_long_long_v<static_cast<unsigned long long>(details::parse_unsigned_number({C...}))>;
}

template <char... C>
constexpr decltype(auto) operator""_stc()
{
  return size_t_v<static_cast<size_t>(details::parse_unsigned_number({C...}))>;
}

} // namespace blackmagic::integral::literals
