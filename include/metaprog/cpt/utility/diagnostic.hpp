#pragma once

#ifndef METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
#define METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_

#include "concepts.hpp"

namespace cpt::utility::diagnostic {

// indirection
template <typename T>
constexpr void diagnostic(decltype(concepts::Indirection))
{
  static_assert(concepts::Indirection.check<T>(), "Expression < *a > is ill-formed.");
}

// address_of
template <typename T>
constexpr void diagnostic(decltype(concepts::AddressOf))
{
  static_assert(concepts::AddressOf.check<T>(), "Expression < &a > is ill-formed.");
}

// subscript
template <typename T, typename I>
constexpr void diagnostic(decltype(concepts::Subscript))
{
  static_assert(concepts::Subscript.check<T, I>(), "Expression < a[b] > is ill-formed.");
}

// pointer_to_member_of_object
template <typename T, typename I>
constexpr void diagnostic(decltype(concepts::PointerToMemberOfObject))
{
  static_assert(concepts::PointerToMemberOfObject.check<T, I>(), "Expression < a.*b > is ill-formed.");
}

// pointer_to_member_of_pointer
template <typename T, typename I>
constexpr void diagnostic(decltype(concepts::PointerToMemberOfPointer))
{
  static_assert(concepts::PointerToMemberOfPointer.check<T, I>(), "Expression < a->*b > is ill-formed.");
}


// assignement

// assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Assignable))
{
  static_assert(concepts::Assignable.check<T, U>(), "Expression < a = b > is ill-formed.");
}

// plus_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::PlusAssignable))
{
  static_assert(concepts::PlusAssignable.check<T, U>(), "Expression < a += b > is ill-formed.");
}

// less_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LessAssignable))
{
  static_assert(concepts::LessAssignable.check<T, U>(), "Expression < a -= b > is ill-formed.");
}

// mult_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::MultAssignable))
{
  static_assert(concepts::MultAssignable.check<T, U>(), "Expression < a *= b > is ill-formed.");
}

// div_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::DivAssignable))
{
  static_assert(concepts::DivAssignable.check<T, U>(), "Expression < a /= b > is ill-formed.");
}

// mod_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::ModAssignable))
{
  static_assert(concepts::ModAssignable.check<T, U>(), "Expression < a %= b > is ill-formed.");
}

// and_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::AndAssignable))
{
  static_assert(concepts::AndAssignable.check<T, U>(), "Expression < a &= b > is ill-formed.");
}

// or_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::OrAssignable))
{
  static_assert(concepts::OrAssignable.check<T, U>(), "Expression < a |= b > is ill-formed.");
}

// xor_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::XorAssignable))
{
  static_assert(concepts::XorAssignable.check<T, U>(), "Expression < a ^= b > is ill-formed.");
}

// lshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LshiftAssignable))
{
  static_assert(concepts::LshiftAssignable.check<T, U>(), "Expression < a <<= b > is ill-formed.");
}

// rshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::RshiftAssignable))
{
  static_assert(concepts::RshiftAssignable.check<T, U>(), "Expression < a >>= b > is ill-formed.");
}


// arithmetic

// positive
template <typename T>
constexpr void diagnostic(decltype(concepts::Positive))
{
  static_assert(concepts::Positive.check<T>(), "Expression < +a > is ill-formed.");
}

// negative
template <typename T>
constexpr void diagnostic(decltype(concepts::Negative))
{
  static_assert(concepts::Negative.check<T>(), "Expression < -a > is ill-formed.");
}

// not
template <typename T>
constexpr void diagnostic(decltype(concepts::Not))
{
  static_assert(concepts::Not.check<T>(), "Expression < ~a > is ill-formed.");
}

// plus
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Plus))
{
  static_assert(concepts::Plus.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// less
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Less))
{
  static_assert(concepts::Less.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// mult
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Mult))
{
  static_assert(concepts::Mult.check<T, U>(), "Expression < a * b > is ill-formed.");
}

// div
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Div))
{
  static_assert(concepts::Div.check<T, U>(), "Expression < a / b > is ill-formed.");
}

// mod
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Mod))
{
  static_assert(concepts::Mod.check<T, U>(), "Expression < a % b > is ill-formed.");
}

// and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::And))
{
  static_assert(concepts::And.check<T, U>(), "Expression < a & b > is ill-formed.");
}

// or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Or))
{
  static_assert(concepts::Or.check<T, U>(), "Expression < a | b > is ill-formed.");
}

// xor
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Xor))
{
  static_assert(concepts::Xor.check<T, U>(), "Expression < a ^ b > is ill-formed.");
}

// lshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Lshift))
{
  static_assert(concepts::Lshift.check<T, U>(), "Expression < a << b > is ill-formed.");
}

// rshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Rshift))
{
  static_assert(concepts::Rshift.check<T, U>(), "Expression < a >> b > is ill-formed.");
}


// increment / decrement

// pre_incrementable
template <typename T>
constexpr void diagnostic(decltype(concepts::PreIncrementable))
{
  static_assert(concepts::PreIncrementable.check<T>(), "Expression < ++a > is ill-formed.");
}

// post_incrementable
template <typename T>
constexpr void diagnostic(decltype(concepts::PostIncrementable))
{
  static_assert(concepts::PostIncrementable.check<T>(), "Expression < a++ > is ill-formed.");
}

// pre_decrementable
template <typename T>
constexpr void diagnostic(decltype(concepts::PreDecrementable))
{
  static_assert(concepts::PreDecrementable.check<T>(), "Expression < --a > is ill-formed.");
}

// post_decrementable
template <typename T>
constexpr void diagnostic(decltype(concepts::PostDecrementable))
{
  static_assert(concepts::PostDecrementable.check<T>(), "Expression < a-- > is ill-formed.");
}


// comparison

// equality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Equality))
{
  static_assert(concepts::Equality.check<T, U>(), "Expression < a == b > is ill-formed.");
}

// inequality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Inequality))
{
  static_assert(concepts::Inequality.check<T, U>(), "Expression < a != b > is ill-formed.");
}

// less_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LessThan))
{
  static_assert(concepts::LessThan.check<T, U>(), "Expression < a < b > is ill-formed.");
}

// less_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LessEqualThan))
{
  static_assert(concepts::LessEqualThan.check<T, U>(), "Expression < a <= b > is ill-formed.");
}

// greater_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::GreaterThan))
{
  static_assert(concepts::GreaterThan.check<T, U>(), "Expression < a > b > is ill-formed.");
}

// greater_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::GreaterEqualThan))
{
  static_assert(concepts::GreaterEqualThan.check<T, U>(), "Expression < a >= b > is ill-formed.");
}


// logical

// logical_not
template <typename T>
constexpr void diagnostic(decltype(concepts::LogicalNot))
{
  static_assert(concepts::LogicalNot.check<T>(), "Expression < !a > is ill-formed.");
}

// logical_and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LogicalAnd))
{
  static_assert(concepts::LogicalAnd.check<T, U>(), "Expression < a && b > is ill-formed.");
}

// logical_or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::LogicalOr))
{
  static_assert(concepts::LogicalOr.check<T, U>(), "Expression < a || b > is ill-formed.");
}


// other

// comma
template <typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Comma))
{
  static_assert(concepts::Comma.check<T, U>(), "Expression < a, b > is ill-formed.");
}

// ternary
template <typename B, typename T, typename U = T>
constexpr void diagnostic(decltype(concepts::Ternary))
{
  static_assert(concepts::Ternary.check<B, T, U>(), "Expression < expr ? a : b > is ill-formed.");
}

// invocable
template <typename F, typename... Args>
constexpr void diagnostic(decltype(concepts::Invocable))
{
  static_assert(concepts::Invocable.check<F, Args...>(), "Expression < std::invoke(func, args...) > is ill-formed.");
}

// invocable r
template <typename R, typename F, typename... Args>
constexpr void diagnostic(decltype(concepts::InvocableR))
{
  static_assert(concepts::InvocableR.check<R, F, Args...>(),
                "Expression < ret = std::invoke(func, args...) > is ill-formed.");
}

} // namespace cpt::utility::diagnostic

#endif // METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
