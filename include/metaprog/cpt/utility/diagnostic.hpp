#pragma once

#ifndef METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
#define METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../verif.hpp"

namespace cpt { namespace utility { namespace diagnostic {

// indirection
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::indirection))
{
  static_assert(cpt::check<T>(cpt::concepts::indirection), "Expression < *a > is ill-formed.");
}

// address_of
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::address_of))
{
  static_assert(cpt::check<T>(cpt::concepts::address_of), "Expression < &a > is ill-formed.");
}

// subscript
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::subscript))
{
  static_assert(cpt::check<T, I>(cpt::concepts::subscript), "Expression < a[b] > is ill-formed.");
}

// pointer_to_member_of_object
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::pointer_to_member_of_object))
{
  static_assert(cpt::check<T, I>(cpt::concepts::pointer_to_member_of_object), "Expression < a.*b > is ill-formed.");
}

// pointer_to_member_of_pointer
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::pointer_to_member_of_pointer))
{
  static_assert(cpt::check<T, I>(cpt::concepts::pointer_to_member_of_pointer), "Expression < a->*b > is ill-formed.");
}


// assignement

// assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::assignable), "Expression < a = b > is ill-formed.");
}

// plus_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::plus_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::plus_assignable), "Expression < a += b > is ill-formed.");
}

// less_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::less_assignable), "Expression < a -= b > is ill-formed.");
}

// mult_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mult_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::mult_assignable), "Expression < a *= b > is ill-formed.");
}

// div_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::div_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::div_assignable), "Expression < a /= b > is ill-formed.");
}

// mod_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mod_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::mod_assignable), "Expression < a %= b > is ill-formed.");
}

// and_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::and_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::and_assignable), "Expression < a &= b > is ill-formed.");
}

// or_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::or_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::or_assignable), "Expression < a |= b > is ill-formed.");
}

// xor_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::xor_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::xor_assignable), "Expression < a ^= b > is ill-formed.");
}

// lshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::lshift_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::lshift_assignable), "Expression < a <<= b > is ill-formed.");
}

// rshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::rshift_assignable))
{
  static_assert(cpt::check<T, U>(cpt::concepts::rshift_assignable), "Expression < a >>= b > is ill-formed.");
}


// arithmetic

// positive
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::positive))
{
  static_assert(cpt::check<T>(cpt::concepts::positive), "Expression < +a > is ill-formed.");
}

// negative
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::negative))
{
  static_assert(cpt::check<T>(cpt::concepts::negative), "Expression < -a > is ill-formed.");
}

// not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Not))
{
  static_assert(cpt::check<T>(cpt::concepts::Not), "Expression < ~a > is ill-formed.");
}

// plus
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::plus))
{
  static_assert(cpt::check<T, U>(cpt::concepts::plus), "Expression < a + b > is ill-formed.");
}

// less
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less))
{
  static_assert(cpt::check<T, U>(cpt::concepts::less), "Expression < a + b > is ill-formed.");
}

// mult
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mult))
{
  static_assert(cpt::check<T, U>(cpt::concepts::mult), "Expression < a * b > is ill-formed.");
}

// div
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::div))
{
  static_assert(cpt::check<T, U>(cpt::concepts::div), "Expression < a / b > is ill-formed.");
}

// mod
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mod))
{
  static_assert(cpt::check<T, U>(cpt::concepts::mod), "Expression < a % b > is ill-formed.");
}

// and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::And))
{
  static_assert(cpt::check<T, U>(cpt::concepts::And), "Expression < a & b > is ill-formed.");
}

// or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Or))
{
  static_assert(cpt::check<T, U>(cpt::concepts::Or), "Expression < a | b > is ill-formed.");
}

// xor
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Xor))
{
  static_assert(cpt::check<T, U>(cpt::concepts::Xor), "Expression < a ^ b > is ill-formed.");
}

// lshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::lshift))
{
  static_assert(cpt::check<T, U>(cpt::concepts::lshift), "Expression < a << b > is ill-formed.");
}

// rshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::rshift))
{
  static_assert(cpt::check<T, U>(cpt::concepts::rshift), "Expression < a >> b > is ill-formed.");
}


// increment / decrement

// pre_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::pre_incrementable))
{
  static_assert(cpt::check<T>(cpt::concepts::pre_incrementable), "Expression < ++a > is ill-formed.");
}

// post_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::post_incrementable))
{
  static_assert(cpt::check<T>(cpt::concepts::post_incrementable), "Expression < a++ > is ill-formed.");
}

// pre_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::pre_decrementable))
{
  static_assert(cpt::check<T>(cpt::concepts::pre_decrementable), "Expression < --a > is ill-formed.");
}

// post_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::post_decrementable))
{
  static_assert(cpt::check<T>(cpt::concepts::post_decrementable), "Expression < a-- > is ill-formed.");
}


// comparison

// equality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::equality))
{
  static_assert(cpt::check<T, U>(cpt::concepts::equality), "Expression < a == b > is ill-formed.");
}

// inequality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::inequality))
{
  static_assert(cpt::check<T, U>(cpt::concepts::inequality), "Expression < a != b > is ill-formed.");
}

// less_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_than))
{
  static_assert(cpt::check<T, U>(cpt::concepts::less_than), "Expression < a < b > is ill-formed.");
}

// less_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_equal_than))
{
  static_assert(cpt::check<T>(cpt::concepts::less_equal_than), "Expression < a <= b > is ill-formed.");
}

// greater_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::greater_than))
{
  static_assert(cpt::check<T, U>(cpt::concepts::greater_than), "Expression < a > b > is ill-formed.");
}

// greater_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::greater_equal_than))
{
  static_assert(cpt::check<T, U>(cpt::concepts::greater_equal_than), "Expression < a >= b > is ill-formed.");
}


// logical

// logical_not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::logical_not))
{
  static_assert(cpt::check<T>(cpt::concepts::logical_not), "Expression < !a > is ill-formed.");
}

// logical_and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::logical_and))
{
  static_assert(cpt::check<T, U>(cpt::concepts::logical_and), "Expression < a && b > is ill-formed.");
}

// logical_or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::logical_or))
{
  static_assert(cpt::check<T, U>(cpt::concepts::logical_or), "Expression < a || b > is ill-formed.");
}


// other

// comma
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::comma))
{
  static_assert(cpt::check<T, U>(cpt::concepts::comma), "Expression < a, b > is ill-formed.");
}

// ternary
template <typename B, typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::ternary))
{
  static_assert(cpt::check<B, T, U>(cpt::concepts::ternary), "Expression < expr ? a : b > is ill-formed.");
}

// invocable
template <typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::invocable))
{
  static_assert(cpt::check<F, Args...>(cpt::concepts::invocable),
                "Expression < std::invoke(func, args...) > is ill-formed.");
}

// invocable r
template <typename R, typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::invocable_r))
{
  static_assert(cpt::check<R, F, Args...>(cpt::concepts::invocable_r),
                "Expression < ret = std::invoke(func, args...) > is ill-formed.");
}

}}} // namespace cpt::utility::diagnostic

#endif // METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
