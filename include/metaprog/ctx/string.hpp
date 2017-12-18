#pragma once

#ifndef CTX_STRING_HPP_
#define CTX_STRING_HPP_

#include "algorithm.hpp"
#include "vector.hpp"

#include <array>
#include <cstddef>
#include <string_view>

namespace ctx {

struct static_string {
  template <std::size_t N>
  constexpr static_string(const char (&str)[N])
    : m_size(N - 1)
    , m_data(&str[0])
  {
  }
  constexpr static_string(const char* str, std::size_t s)
    : m_size(s)
    , m_data(str)
  {
  }

  constexpr static_string() = default;

  constexpr size_t size() const
  {
    return m_size;
  }

  constexpr const char* c_str() const
  {
    return m_data;
  }

  constexpr const char* begin() const
  {
    return m_data;
  }

  constexpr const char* end() const
  {
    return m_data + m_size;
  }

  std::size_t m_size{0};
  const char* m_data = nullptr;
};

constexpr bool operator==(const static_string& x, const static_string& y)
{
  return equal(x.begin(), x.end(), y.begin(), y.end());
}


// note that this works because vector is implicitly null terminated with its data initializer
template <typename CharType, size_t Size>
struct basic_string : vector<CharType, Size> {
  constexpr basic_string(const static_string& s)
    : vector<CharType, Size>(s.begin(), s.end())
  {
  }
  constexpr basic_string(const std::string_view& s)
    : vector<CharType, Size>(s.cbegin(), s.cend())
  {
  }

  constexpr basic_string() = default;

  constexpr basic_string& operator=(const static_string& s)
  {
    return *this = basic_string(s);
  }

  constexpr basic_string& operator=(const std::string_view& s)
  {
    return *this = basic_string(s);
  }

  constexpr const char* c_str() const
  {
    return this->data();
  }
};

template <typename CharType, size_t Size>
constexpr bool operator==(const basic_string<CharType, Size>& lhs, const static_string& rhs)
{
  return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename CharType, size_t Size>
constexpr bool operator==(const basic_string<CharType, Size>& lhs, const std::string_view& rhs)
{
  return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

using string = basic_string<char, 32>;

inline namespace literals {
constexpr auto operator""_s(const char* str, size_t s)
{
  return string{static_string{str, s}};
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4455 ) // 'operator ""sv': literal suffix identifiers that do not start with an underscore are reserved
#endif
using std::literals::operator""sv;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
} // namespace literals

} // namespace ctx

#endif // CTX_STRING_HPP_