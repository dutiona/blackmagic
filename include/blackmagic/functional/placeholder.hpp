#pragma once

#include "partial.hpp"
#include "reverse_partial.hpp"
#include "utility.hpp"

#include <type_traits>
#include <utility>

namespace blackmagic::functional::placeholder {

struct placeholder_t {
  constexpr placeholder_t()                     = default;
  constexpr placeholder_t(const placeholder_t&) = default;
  constexpr placeholder_t(placeholder_t&&)      = default;

  constexpr decltype(auto) operator=(const placeholder_t&) const
  {
    return partial(assignable);
  }
  template <typename T>
  constexpr decltype(auto) operator=(T&& v) const
  {
    return reverse_partial(assignable, std::forward<T>(v));
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
  return partial(binary_plus);
}
template <typename T>
constexpr decltype(auto) operator+(T&& v, const placeholder_t&)
{
  return partial(binary_plus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator+(const placeholder_t&, T&& v)
{
  return reverse_partial(binary_plus, std::forward<T>(v));
}

// binary -
constexpr decltype(auto) operator-(const placeholder_t&, const placeholder_t&)
{
  return partial(binary_minus);
}
template <typename T>
constexpr decltype(auto) operator-(T&& v, const placeholder_t&)
{
  return partial(binary_minus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator-(const placeholder_t&, T&& v)
{
  return reverse_partial(binary_minus, std::forward<T>(v));
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
  return partial(unary_plus);
}

// unary -
constexpr decltype(auto) operator-(const placeholder_t&)
{
  return partial(unary_minus);
}

inline namespace assignement {
// +=
constexpr decltype(auto) operator+=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_plus);
}
template <typename T>
constexpr decltype(auto) operator+=(T&& v, const placeholder_t&)
{
  return partial(assignable_plus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator+=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_plus, std::forward<T>(v));
}

// -=
constexpr decltype(auto) operator-=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_minus);
}
template <typename T>
constexpr decltype(auto) operator-=(T&& v, const placeholder_t&)
{
  return partial(assignable_minus, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator-=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_minus, std::forward<T>(v));
}

// *=
constexpr decltype(auto) operator*=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_mult);
}
template <typename T>
constexpr decltype(auto) operator*=(T&& v, const placeholder_t&)
{
  return partial(assignable_mult, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator*=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_mult, std::forward<T>(v));
}

// /=
constexpr decltype(auto) operator/=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_div);
}
template <typename T>
constexpr decltype(auto) operator/=(T&& v, const placeholder_t&)
{
  return partial(assignable_div, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator/=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_div, std::forward<T>(v));
}

// %=
constexpr decltype(auto) operator%=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_mod);
}
template <typename T>
constexpr decltype(auto) operator%=(T&& v, const placeholder_t&)
{
  return partial(assignable_mod, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator%=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_mod, std::forward<T>(v));
}

} // namespace assignement

} // namespace arithmetic


inline namespace bitwise {
// ~
constexpr decltype(auto) operator~(const placeholder_t&)
{
  return partial(Not);
}
// &
constexpr decltype(auto) operator&(const placeholder_t&, const placeholder_t&)
{
  return partial(And);
}
template <typename T>
constexpr decltype(auto) operator&(T&& v, const placeholder_t&)
{
  return partial(And, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator&(const placeholder_t&, T&& v)
{
  return reverse_partial(And, std::forward<T>(v));
}

// |
constexpr decltype(auto) operator|(const placeholder_t&, const placeholder_t&)
{
  return partial(Or);
}
template <typename T>
constexpr decltype(auto) operator|(T&& v, const placeholder_t&)
{
  return partial(Or, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator|(const placeholder_t&, T&& v)
{
  return reverse_partial(Or, std::forward<T>(v));
}

// ^
constexpr decltype(auto) operator^(const placeholder_t&, const placeholder_t&)
{
  return partial(Xor);
}
template <typename T>
constexpr decltype(auto) operator^(T&& v, const placeholder_t&)
{
  return partial(Xor, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator^(const placeholder_t&, T&& v)
{
  return reverse_partial(Xor, std::forward<T>(v));
}

// <<
constexpr decltype(auto) operator<<(const placeholder_t&, const placeholder_t&)
{
  return partial(lshift);
}
template <typename T>
constexpr decltype(auto) operator<<(T&& v, const placeholder_t&)
{
  return partial(lshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<<(const placeholder_t&, T&& v)
{
  return reverse_partial(lshift, std::forward<T>(v));
}

// >>
constexpr decltype(auto) operator>>(const placeholder_t&, const placeholder_t&)
{
  return partial(rshift);
}
template <typename T>
constexpr decltype(auto) operator>>(T&& v, const placeholder_t&)
{
  return partial(rshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>>(const placeholder_t&, T&& v)
{
  return reverse_partial(rshift, std::forward<T>(v));
}

inline namespace assignement {
// &=
constexpr decltype(auto) operator&=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_and);
}
template <typename T>
constexpr decltype(auto) operator&=(T&& v, const placeholder_t&)
{
  return partial(assignable_and, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator&=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_and, std::forward<T>(v));
}

// |=
constexpr decltype(auto) operator|=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_or);
}
template <typename T>
constexpr decltype(auto) operator|=(T&& v, const placeholder_t&)
{
  return partial(assignable_or, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator|=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_or, std::forward<T>(v));
}

// ^=
constexpr decltype(auto) operator^=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_xor);
}
template <typename T>
constexpr decltype(auto) operator^=(T&& v, const placeholder_t&)
{
  return partial(assignable_xor, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator^=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_xor, std::forward<T>(v));
}

// <<=
constexpr decltype(auto) operator<<=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_lshift);
}
template <typename T>
constexpr decltype(auto) operator<<=(T&& v, const placeholder_t&)
{
  return partial(assignable_lshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<<=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_lshift, std::forward<T>(v));
}

// >>=
constexpr decltype(auto) operator>>=(const placeholder_t&, const placeholder_t&)
{
  return partial(assignable_rshift);
}
template <typename T>
constexpr decltype(auto) operator>>=(T&& v, const placeholder_t&)
{
  return partial(assignable_rshift, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>>=(const placeholder_t&, T&& v)
{
  return reverse_partial(assignable_rshift, std::forward<T>(v));
}

} // namespace assignement

} // namespace bitwise


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
  return partial(less_than);
}
template <typename T>
constexpr decltype(auto) operator<(T&& v, const placeholder_t&)
{
  return partial(less_than, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<(const placeholder_t&, T&& v)
{
  return reverse_partial(less_than, std::forward<T>(v));
}

// <=
constexpr decltype(auto) operator<=(const placeholder_t&, const placeholder_t&)
{
  return partial(less_equal_than);
}
template <typename T>
constexpr decltype(auto) operator<=(T&& v, const placeholder_t&)
{
  return partial(less_equal_than, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator<=(const placeholder_t&, T&& v)
{
  return reverse_partial(less_equal_than, std::forward<T>(v));
}

// >
constexpr decltype(auto) operator>(const placeholder_t&, const placeholder_t&)
{
  return partial(greater_than);
}
template <typename T>
constexpr decltype(auto) operator>(T&& v, const placeholder_t&)
{
  return partial(greater_than, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>(const placeholder_t&, T&& v)
{
  return reverse_partial(greater_than, std::forward<T>(v));
}

// >=
constexpr decltype(auto) operator>=(const placeholder_t&, const placeholder_t&)
{
  return partial(greater_equal_than);
}
template <typename T>
constexpr decltype(auto) operator>=(T&& v, const placeholder_t&)
{
  return partial(greater_equal_than, std::forward<T>(v));
}
template <typename T>
constexpr decltype(auto) operator>=(const placeholder_t&, T&& v)
{
  return reverse_partial(greater_equal_than, std::forward<T>(v));
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
