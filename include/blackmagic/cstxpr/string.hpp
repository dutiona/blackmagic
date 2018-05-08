#pragma once

#include "algorithm.hpp"
#include "vector.hpp"

#include <cstddef>
#include <string_view>

namespace blackmagic::cstxpr {

struct static_string {
  template <size_t N>
  constexpr static_string(const char (&str)[N])
    : m_size(N - 1)
    , m_data(&str[0])
  {
  }
  constexpr static_string(const char* str, size_t s)
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

  size_t      m_size{0};
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

using namespace std::literals;

} // namespace literals

} // namespace blackmagic::cstxpr
