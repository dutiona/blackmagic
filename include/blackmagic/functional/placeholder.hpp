#pragma once

#include "partial.hpp"
#include "reverse_partial.hpp"
#include "utility.hpp"

#include <utility>

namespace blackmagic::functional::placeholder {

struct placeholder_t {
  constexpr placeholder_t()                     = default;
  constexpr placeholder_t(const placeholder_t&) = default;
  constexpr placeholder_t(placeholder_t&&)      = default;

  constexpr decltype(auto) operator=(const placeholder_t&) const
  {
    return partial(assign);
  }
  template <typename T>
  constexpr decltype(auto) operator=(T&& v) const
  {
    return reverse_partial(assign, std::forward<T>(v));
  }

  constexpr decltype(auto) operator[](const placeholder_t&) const
  {
    return partial(subscript);
  }
  template <typename T>
  constexpr decltype(auto) operator[](T&& v) const
  {
    return reverse_partial(subscript, std::forward<T>(v));
  }

  constexpr decltype(auto) operator++() const
  {
    return partial(preincrement);
  }
  constexpr decltype(auto) operator++(int) const
  {
    return partial(postincrement);
  }
  constexpr decltype(auto) operator--() const
  {
    return partial(predecrement);
  }
  constexpr decltype(auto) operator--(int) const
  {
    return partial(postdecrement);
  }

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
  {
    return reverse_partial(invocable, std::forward<Args>(args)...);
  }
};

inline namespace operators {
inline namespace member_access {
// *
constexpr decltype(auto) operator*(const placeholder_t&)
{
  return partial(indirection);
}

// &
constexpr decltype(auto) operator&(const placeholder_t&)
{
  return partial(address_of);
}

} // namespace member_access


inline namespace arithmetic {
// binary +
constexpr decltype(auto) operator+(const placeholder_t&, const placeholder_t&)
{
  return partial(plus);
}
template <typename T>
constexpr decltype(auto) operator+(T&& v, const placeholder_t&)
{
  return partial(plus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator+(const placeholder_t&, T&& v)
{
  return reverse_partial(plus, std::forward<T>(v));
}

// binary -
constexpr decltype(auto) operator-(const placeholder_t&, const placeholder_t&)
{
  return partial(minus);
}
template <typename T>
constexpr decltype(auto) operator-(T&& v, const placeholder_t&)
{
  return partial(minus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator-(const placeholder_t&, T&& v)
{
  return reverse_partial(minus, std::forward<T>(v));
}

// *
constexpr decltype(auto) operator*(const placeholder_t&, const placeholder_t&)
{
  return partial(mult);
}
template <typename T>
constexpr decltype(auto) operator*(T&& v, const placeholder_t&)
{
  return partial(mult, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator*(const placeholder_t&, T&& v)
{
  return reverse_partial(mult, std::forward<T>(v));
}

// /
constexpr decltype(auto) operator/(const placeholder_t&, const placeholder_t&)
{
  return partial(div);
}
template <typename T>
constexpr decltype(auto) operator/(T&& v, const placeholder_t&)
{
  return partial(div, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator/(const placeholder_t&, T&& v)
{
  return reverse_partial(div, std::forward<T>(v));
}

// %
constexpr decltype(auto) operator%(const placeholder_t&, const placeholder_t&)
{
  return partial(mod);
}
template <typename T>
constexpr decltype(auto) operator%(T&& v, const placeholder_t&)
{
  return partial(mod, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator%(const placeholder_t&, T&& v)
{
  return reverse_partial(mod, std::forward<T>(v));
}

// unary +
constexpr decltype(auto) operator+(const placeholder_t&)
{
  return partial(positive);
}

// unary -
constexpr decltype(auto) operator-(const placeholder_t&)
{
  return partial(negative);
}

// ~
constexpr decltype(auto) operator~(const placeholder_t&)
{
  return partial(bit_not);
}
// &
constexpr decltype(auto) operator&(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_and);
}
template <typename T>
constexpr decltype(auto) operator&(T&& v, const placeholder_t&)
{
  return partial(bit_and, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator&(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_and, std::forward<T>(v));
}

// |
constexpr decltype(auto) operator|(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_or);
}
template <typename T>
constexpr decltype(auto) operator|(T&& v, const placeholder_t&)
{
  return partial(bit_or, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator|(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_or, std::forward<T>(v));
}

// ^
constexpr decltype(auto) operator^(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_xor);
}
template <typename T>
constexpr decltype(auto) operator^(T&& v, const placeholder_t&)
{
  return partial(bit_xor, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator^(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_xor, std::forward<T>(v));
}

// <<
constexpr decltype(auto) operator<<(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_lshift);
}
template <typename T>
constexpr decltype(auto) operator<<(T&& v, const placeholder_t&)
{
  return partial(bit_lshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<<(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_lshift, std::forward<T>(v));
}

// >>
constexpr decltype(auto) operator>>(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_rshift);
}
template <typename T>
constexpr decltype(auto) operator>>(T&& v, const placeholder_t&)
{
  return partial(bit_rshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>>(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_rshift, std::forward<T>(v));
}


inline namespace assignement {
// +=
constexpr decltype(auto) operator+=(const placeholder_t&, const placeholder_t&)
{
  return partial(plus_assign);
}
template <typename T>
constexpr decltype(auto) operator+=(T&& v, const placeholder_t&)
{
  return partial(plus_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator+=(const placeholder_t&, T&& v)
{
  return reverse_partial(plus_assign, std::forward<T>(v));
}

// -=
constexpr decltype(auto) operator-=(const placeholder_t&, const placeholder_t&)
{
  return partial(minus_assign);
}
template <typename T>
constexpr decltype(auto) operator-=(T&& v, const placeholder_t&)
{
  return partial(minus_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator-=(const placeholder_t&, T&& v)
{
  return reverse_partial(minus_assign, std::forward<T>(v));
}

// *=
constexpr decltype(auto) operator*=(const placeholder_t&, const placeholder_t&)
{
  return partial(mult_assign);
}
template <typename T>
constexpr decltype(auto) operator*=(T&& v, const placeholder_t&)
{
  return partial(mult_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator*=(const placeholder_t&, T&& v)
{
  return reverse_partial(mult_assign, std::forward<T>(v));
}

// /=
constexpr decltype(auto) operator/=(const placeholder_t&, const placeholder_t&)
{
  return partial(div_assign);
}
template <typename T>
constexpr decltype(auto) operator/=(T&& v, const placeholder_t&)
{
  return partial(div_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator/=(const placeholder_t&, T&& v)
{
  return reverse_partial(div_assign, std::forward<T>(v));
}

// %=
constexpr decltype(auto) operator%=(const placeholder_t&, const placeholder_t&)
{
  return partial(mod_assign);
}
template <typename T>
constexpr decltype(auto) operator%=(T&& v, const placeholder_t&)
{
  return partial(mod_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator%=(const placeholder_t&, T&& v)
{
  return reverse_partial(mod_assign, std::forward<T>(v));
}

// &=
constexpr decltype(auto) operator&=(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_and_assign);
}
template <typename T>
constexpr decltype(auto) operator&=(T&& v, const placeholder_t&)
{
  return partial(bit_and_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator&=(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_and_assign, std::forward<T>(v));
}

// |=
constexpr decltype(auto) operator|=(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_or_assign);
}
template <typename T>
constexpr decltype(auto) operator|=(T&& v, const placeholder_t&)
{
  return partial(bit_or_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator|=(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_or_assign, std::forward<T>(v));
}

// ^=
constexpr decltype(auto) operator^=(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_xor_assign);
}
template <typename T>
constexpr decltype(auto) operator^=(T&& v, const placeholder_t&)
{
  return partial(bit_xor_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator^=(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_xor_assign, std::forward<T>(v));
}

// <<=
constexpr decltype(auto) operator<<=(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_lshift_assign);
}
template <typename T>
constexpr decltype(auto) operator<<=(T&& v, const placeholder_t&)
{
  return partial(bit_lshift_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<<=(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_lshift_assign, std::forward<T>(v));
}

// >>=
constexpr decltype(auto) operator>>=(const placeholder_t&, const placeholder_t&)
{
  return partial(bit_rshift_assign);
}
template <typename T>
constexpr decltype(auto) operator>>=(T&& v, const placeholder_t&)
{
  return partial(bit_rshift_assign, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>>=(const placeholder_t&, T&& v)
{
  return reverse_partial(bit_rshift_assign, std::forward<T>(v));
}

} // namespace assignement

} // namespace arithmetic


inline namespace comparison {
// ==
constexpr decltype(auto) operator==(const placeholder_t&, const placeholder_t&)
{
  return partial(equal);
}
template <typename T>
constexpr decltype(auto) operator==(T&& v, const placeholder_t&)
{
  return partial(equal, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator==(const placeholder_t&, T&& v)
{
  return reverse_partial(equal, std::forward<T>(v));
}

// !=
constexpr decltype(auto) operator!=(const placeholder_t&, const placeholder_t&)
{
  return partial(not_equal);
}
template <typename T>
constexpr decltype(auto) operator!=(T&& v, const placeholder_t&)
{
  return partial(not_equal, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator!=(const placeholder_t&, T&& v)
{
  return reverse_partial(not_equal, std::forward<T>(v));
}

// <
constexpr decltype(auto) operator<(const placeholder_t&, const placeholder_t&)
{
  return partial(less);
}
template <typename T>
constexpr decltype(auto) operator<(T&& v, const placeholder_t&)
{
  return partial(less, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<(const placeholder_t&, T&& v)
{
  return reverse_partial(less, std::forward<T>(v));
}

// <=
constexpr decltype(auto) operator<=(const placeholder_t&, const placeholder_t&)
{
  return partial(less_equal);
}
template <typename T>
constexpr decltype(auto) operator<=(T&& v, const placeholder_t&)
{
  return partial(less_equal, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<=(const placeholder_t&, T&& v)
{
  return reverse_partial(less_equal, std::forward<T>(v));
}

// >
constexpr decltype(auto) operator>(const placeholder_t&, const placeholder_t&)
{
  return partial(greater);
}
template <typename T>
constexpr decltype(auto) operator>(T&& v, const placeholder_t&)
{
  return partial(greater, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>(const placeholder_t&, T&& v)
{
  return reverse_partial(greater, std::forward<T>(v));
}

// >=
constexpr decltype(auto) operator>=(const placeholder_t&, const placeholder_t&)
{
  return partial(greater_equal);
}
template <typename T>
constexpr decltype(auto) operator>=(T&& v, const placeholder_t&)
{
  return partial(greater_equal, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>=(const placeholder_t&, T&& v)
{
  return reverse_partial(greater_equal, std::forward<T>(v));
}

} // namespace comparison


inline namespace logical {
// &&
constexpr decltype(auto) operator&&(const placeholder_t&, const placeholder_t&)
{
  return partial(logical_and);
}
template <typename T>
constexpr decltype(auto) operator&&(T&& v, const placeholder_t&)
{
  return partial(logical_and, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator&&(const placeholder_t&, T&& v)
{
  return reverse_partial(logical_and, std::forward<T>(v));
}

// ||
constexpr decltype(auto) operator||(const placeholder_t&, const placeholder_t&)
{
  return partial(logical_or);
}
template <typename T>
constexpr decltype(auto) operator||(T&& v, const placeholder_t&)
{
  return partial(logical_or, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator||(const placeholder_t&, T&& v)
{
  return reverse_partial(logical_or, std::forward<T>(v));
}

// !
constexpr decltype(auto) operator!(const placeholder_t&)
{
  return partial(logical_not);
}

} // namespace logical


} // namespace operators

inline constexpr const placeholder_t _{};

} // namespace blackmagic::functional::placeholder
