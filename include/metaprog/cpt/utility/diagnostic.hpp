#pragma once

#ifndef METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
#define METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../core.hpp"

namespace cpt { namespace utility { namespace diagnostic {

// indirection
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::indirection))
{
  static_assert(cpt::concepts::indirection.check<T>(), "Expression < *a > is ill-formed.");
}

// address_of
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::address_of))
{
  static_assert(cpt::concepts::address_of.check<T>(), "Expression < &a > is ill-formed.");
}

// subscript
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::subscript))
{
  static_assert(cpt::concepts::subscript.check<T, I>(), "Expression < a[b] > is ill-formed.");
}

// pointer_to_member_of_object
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::pointer_to_member_of_object))
{
  static_assert(cpt::concepts::pointer_to_member_of_object.check<T, I>(), "Expression < a.*b > is ill-formed.");
}

// pointer_to_member_of_pointer
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::pointer_to_member_of_pointer))
{
  static_assert(cpt::concepts::pointer_to_member_of_pointer.check<T, I>(), "Expression < a->*b > is ill-formed.");
}


// assignement

// assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::assignable))
{
  static_assert(cpt::concepts::assignable.check<T, U>(), "Expression < a = b > is ill-formed.");
}

// plus_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::plus_assignable))
{
  static_assert(cpt::concepts::plus_assignable.check<T, U>(), "Expression < a += b > is ill-formed.");
}

// less_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_assignable))
{
  static_assert(cpt::concepts::less_assignable.check<T, U>(), "Expression < a -= b > is ill-formed.");
}

// mult_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mult_assignable))
{
  static_assert(cpt::concepts::mult_assignable.check<T, U>(), "Expression < a *= b > is ill-formed.");
}

// div_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::div_assignable))
{
  static_assert(cpt::concepts::div_assignable.check<T, U>(), "Expression < a /= b > is ill-formed.");
}

// mod_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mod_assignable))
{
  static_assert(cpt::concepts::mod_assignable.check<T, U>(), "Expression < a %= b > is ill-formed.");
}

// and_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::and_assignable))
{
  static_assert(cpt::concepts::and_assignable.check<T, U>(), "Expression < a &= b > is ill-formed.");
}

// or_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::or_assignable))
{
  static_assert(cpt::concepts::or_assignable.check<T, U>(), "Expression < a |= b > is ill-formed.");
}

// xor_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::xor_assignable))
{
  static_assert(cpt::concepts::xor_assignable.check<T, U>(), "Expression < a ^= b > is ill-formed.");
}

// lshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::lshift_assignable))
{
  static_assert(cpt::concepts::lshift_assignable.check<T, U>(), "Expression < a <<= b > is ill-formed.");
}

// rshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::rshift_assignable))
{
  static_assert(cpt::concepts::rshift_assignable.check<T, U>(), "Expression < a >>= b > is ill-formed.");
}


// arithmetic

// positive
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::positive))
{
  static_assert(cpt::concepts::positive.check<T>(), "Expression < +a > is ill-formed.");
}

// negative
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::negative))
{
  static_assert(cpt::concepts::negative.check<T>(), "Expression < -a > is ill-formed.");
}

// not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Not))
{
  static_assert(cpt::concepts::Not.check<T>(), "Expression < ~a > is ill-formed.");
}

// plus
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::plus))
{
  static_assert(cpt::concepts::plus.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// less
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less))
{
  static_assert(cpt::concepts::less.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// mult
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mult))
{
  static_assert(cpt::concepts::mult.check<T, U>(), "Expression < a * b > is ill-formed.");
}

// div
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::div))
{
  static_assert(cpt::concepts::div.check<T, U>(), "Expression < a / b > is ill-formed.");
}

// mod
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::mod))
{
  static_assert(cpt::concepts::mod.check<T, U>(), "Expression < a % b > is ill-formed.");
}

// and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::And))
{
  static_assert(cpt::concepts::And.check<T, U>(), "Expression < a & b > is ill-formed.");
}

// or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Or))
{
  static_assert(cpt::concepts::Or.check<T, U>(), "Expression < a | b > is ill-formed.");
}

// xor
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Xor))
{
  static_assert(cpt::concepts::Xor.check<T, U>(), "Expression < a ^ b > is ill-formed.");
}

// lshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::lshift))
{
  static_assert(cpt::concepts::lshift.check<T, U>(), "Expression < a << b > is ill-formed.");
}

// rshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::rshift))
{
  static_assert(cpt::concepts::rshift.check<T, U>(), "Expression < a >> b > is ill-formed.");
}


// increment / decrement

// pre_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::pre_incrementable))
{
  static_assert(cpt::concepts::pre_incrementable.check<T>(), "Expression < ++a > is ill-formed.");
}

// post_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::post_incrementable))
{
  static_assert(cpt::concepts::post_incrementable.check<T>(), "Expression < a++ > is ill-formed.");
}

// pre_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::pre_decrementable))
{
  static_assert(cpt::concepts::pre_decrementable.check<T>(), "Expression < --a > is ill-formed.");
}

// post_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::post_decrementable))
{
  static_assert(cpt::concepts::post_decrementable.check<T>(), "Expression < a-- > is ill-formed.");
}


// comparison

// equality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::equality))
{
  static_assert(cpt::concepts::equality.check<T, U>(), "Expression < a == b > is ill-formed.");
}

// inequality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::inequality))
{
  static_assert(cpt::concepts::inequality.check<T, U>(), "Expression < a != b > is ill-formed.");
}

// less_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_than))
{
  static_assert(cpt::concepts::less_than.check<T, U>(), "Expression < a < b > is ill-formed.");
}

// less_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::less_equal_than))
{
  static_assert(cpt::concepts::less_equal_than.check<T, U>(), "Expression < a <= b > is ill-formed.");
}

// greater_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::greater_than))
{
  static_assert(cpt::concepts::greater_than.check<T, U>(), "Expression < a > b > is ill-formed.");
}

// greater_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::greater_equal_than))
{
  static_assert(cpt::concepts::greater_equal_than.check<T, U>(), "Expression < a >= b > is ill-formed.");
}


// logical

// logical_not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::logical_not))
{
  static_assert(cpt::concepts::logical_not.check<T>(), "Expression < !a > is ill-formed.");
}

// logical_and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::logical_and))
{
  static_assert(cpt::concepts::logical_and.check<T, U>(), "Expression < a && b > is ill-formed.");
}

// logical_or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::logical_or))
{
  static_assert(cpt::concepts::logical_or.check<T, U>(), "Expression < a || b > is ill-formed.");
}


// other

// comma
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::comma))
{
  static_assert(cpt::concepts::comma.check<T, U>(), "Expression < a, b > is ill-formed.");
}

// ternary
template <typename B, typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::ternary))
{
  static_assert(cpt::concepts::ternary.check<B, T, U>(), "Expression < expr ? a : b > is ill-formed.");
}

// invocable
template <typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::invocable))
{
  static_assert(cpt::concepts::invocable.check<F, Args...>(),
                "Expression < std::invoke(func, args...) > is ill-formed.");
}

// invocable r
template <typename R, typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::invocable_r))
{
  static_assert(cpt::concepts::invocable_r.check<R, F, Args...>(),
                "Expression < ret = std::invoke(func, args...) > is ill-formed.");
}

}}} // namespace cpt::utility::diagnostic

#endif // METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
