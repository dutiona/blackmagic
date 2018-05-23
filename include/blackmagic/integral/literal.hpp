#pragma once

#include "types.hpp"

#include <cstddef>

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
  static_assert(N == 4 || N == 5, "Allowed values are 'true' and 'false'!");

  if (N == 4 && arr[0] == 't' && arr[1] == 'r' && arr[2] == 'u' && arr[3] == 'e') {
    return true;
  }
  else if (N == 5 && arr[0] == 'f' && arr[1] == 'a' && arr[2] == 'l' && arr[3] == 's' && arr[4] == 'e') {
    return false;
  }
  else {
    throw "Allowed values are 'true' and 'false'!";
  }
}

template <std::size_t N>
constexpr char parse_char(const char (&arr)[N])
{
  static_assert(N == 1, "Only a single char is allowed!");

  return arr[0];
}

} // namespace details

template <char... C>
constexpr decltype(auto) operator""_c()
{
  return long_long_t<details::parse_signed_number({C...})>{};
}

template <typename CharT, CharT... C>
constexpr decltype(auto) operator""_bc()
{
  return bool_t<details::parse_bool({C...})>{};
}

template <typename CharT, CharT... C>
constexpr decltype(auto) operator""_cc()
{
  return char_t<details::parse_char({C...})>{};
}

template <char... C>
constexpr decltype(auto) operator""_sc()
{
  return short_t<static_cast<short>(details::parse_signed_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_ic()
{
  return int_t<static_cast<int>(details::parse_signed_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_lc()
{
  return long_t<static_cast<long>(details::parse_signed_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_llc()
{
  return long_long_t<details::parse_signed_number({C...})>{};
}

template <typename CharT, CharT... C>
constexpr decltype(auto) operator""_ucc()
{
  return unsigned_char_t<static_cast<unsigned char>(details::parse_char({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_usc()
{
  return unsigned_short_t<static_cast<unsigned short>(details::parse_unsigned_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_uc()
{
  return unsigned_long_long_t<details::parse_unsigned_number({C...})>{};
}

template <char... C>
constexpr decltype(auto) operator""_uic()
{
  return unsigned_int_t<static_cast<unsigned int>(details::parse_unsigned_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_ulc()
{
  return unsigned_long_t<static_cast<unsigned long>(details::parse_unsigned_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_ullc()
{
  return unsigned_long_long_t<static_cast<unsigned long long>(details::parse_unsigned_number({C...}))>{};
}

template <char... C>
constexpr decltype(auto) operator""_stc()
{
  return size_t_t<static_cast<size_t>(details::parse_unsigned_number({C...}))>{};
}

} // namespace blackmagic::integral::literals
