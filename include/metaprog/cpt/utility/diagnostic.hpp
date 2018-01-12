#pragma once

#ifndef METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
#define METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_

#include "concepts.hpp"

#include "../core.hpp"

namespace cpt { namespace utility { namespace diagnostic {

// indirection
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Indirection))
{
  static_assert(cpt::concepts::Indirection.check<T>(), "Expression < *a > is ill-formed.");
}

// address_of
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::AddressOf))
{
  static_assert(cpt::concepts::AddressOf.check<T>(), "Expression < &a > is ill-formed.");
}

// subscript
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::Subscript))
{
  static_assert(cpt::concepts::Subscript.check<T, I>(), "Expression < a[b] > is ill-formed.");
}

// pointer_to_member_of_object
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::PointerToMemberOfObject))
{
  static_assert(cpt::concepts::PointerToMemberOfObject.check<T, I>(), "Expression < a.*b > is ill-formed.");
}

// pointer_to_member_of_pointer
template <typename T, typename I>
constexpr void diagnostic(decltype(cpt::concepts::PointerToMemberOfPointer))
{
  static_assert(cpt::concepts::PointerToMemberOfPointer.check<T, I>(), "Expression < a->*b > is ill-formed.");
}


// assignement

// assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Assignable))
{
  static_assert(cpt::concepts::Assignable.check<T, U>(), "Expression < a = b > is ill-formed.");
}

// plus_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::PlusAssignable))
{
  static_assert(cpt::concepts::PlusAssignable.check<T, U>(), "Expression < a += b > is ill-formed.");
}

// less_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LessAssignable))
{
  static_assert(cpt::concepts::LessAssignable.check<T, U>(), "Expression < a -= b > is ill-formed.");
}

// mult_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::MultAssignable))
{
  static_assert(cpt::concepts::MultAssignable.check<T, U>(), "Expression < a *= b > is ill-formed.");
}

// div_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::DivAssignable))
{
  static_assert(cpt::concepts::DivAssignable.check<T, U>(), "Expression < a /= b > is ill-formed.");
}

// mod_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::ModAssignable))
{
  static_assert(cpt::concepts::ModAssignable.check<T, U>(), "Expression < a %= b > is ill-formed.");
}

// and_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::AndAssignable))
{
  static_assert(cpt::concepts::AndAssignable.check<T, U>(), "Expression < a &= b > is ill-formed.");
}

// or_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::OrAssignable))
{
  static_assert(cpt::concepts::OrAssignable.check<T, U>(), "Expression < a |= b > is ill-formed.");
}

// xor_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::XorAssignable))
{
  static_assert(cpt::concepts::XorAssignable.check<T, U>(), "Expression < a ^= b > is ill-formed.");
}

// lshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LshiftAssignable))
{
  static_assert(cpt::concepts::LshiftAssignable.check<T, U>(), "Expression < a <<= b > is ill-formed.");
}

// rshift_assignable
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::RshiftAssignable))
{
  static_assert(cpt::concepts::RshiftAssignable.check<T, U>(), "Expression < a >>= b > is ill-formed.");
}


// arithmetic

// positive
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Positive))
{
  static_assert(cpt::concepts::Positive.check<T>(), "Expression < +a > is ill-formed.");
}

// negative
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Negative))
{
  static_assert(cpt::concepts::Negative.check<T>(), "Expression < -a > is ill-formed.");
}

// not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::Not))
{
  static_assert(cpt::concepts::Not.check<T>(), "Expression < ~a > is ill-formed.");
}

// plus
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Plus))
{
  static_assert(cpt::concepts::Plus.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// less
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Less))
{
  static_assert(cpt::concepts::Less.check<T, U>(), "Expression < a + b > is ill-formed.");
}

// mult
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Mult))
{
  static_assert(cpt::concepts::Mult.check<T, U>(), "Expression < a * b > is ill-formed.");
}

// div
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Div))
{
  static_assert(cpt::concepts::Div.check<T, U>(), "Expression < a / b > is ill-formed.");
}

// mod
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Mod))
{
  static_assert(cpt::concepts::Mod.check<T, U>(), "Expression < a % b > is ill-formed.");
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
constexpr void diagnostic(decltype(cpt::concepts::Lshift))
{
  static_assert(cpt::concepts::Lshift.check<T, U>(), "Expression < a << b > is ill-formed.");
}

// rshift
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Rshift))
{
  static_assert(cpt::concepts::Rshift.check<T, U>(), "Expression < a >> b > is ill-formed.");
}


// increment / decrement

// pre_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::PreIncrementable))
{
  static_assert(cpt::concepts::PreIncrementable.check<T>(), "Expression < ++a > is ill-formed.");
}

// post_incrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::PostIncrementable))
{
  static_assert(cpt::concepts::PostIncrementable.check<T>(), "Expression < a++ > is ill-formed.");
}

// pre_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::PreDecrementable))
{
  static_assert(cpt::concepts::PreDecrementable.check<T>(), "Expression < --a > is ill-formed.");
}

// post_decrementable
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::PostDecrementable))
{
  static_assert(cpt::concepts::PostDecrementable.check<T>(), "Expression < a-- > is ill-formed.");
}


// comparison

// equality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Equality))
{
  static_assert(cpt::concepts::Equality.check<T, U>(), "Expression < a == b > is ill-formed.");
}

// inequality
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Inequality))
{
  static_assert(cpt::concepts::Inequality.check<T, U>(), "Expression < a != b > is ill-formed.");
}

// less_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LessThan))
{
  static_assert(cpt::concepts::LessThan.check<T, U>(), "Expression < a < b > is ill-formed.");
}

// less_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LessEqualThan))
{
  static_assert(cpt::concepts::LessEqualThan.check<T, U>(), "Expression < a <= b > is ill-formed.");
}

// greater_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::GreaterThan))
{
  static_assert(cpt::concepts::GreaterThan.check<T, U>(), "Expression < a > b > is ill-formed.");
}

// greater_equal_than
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::GreaterEqualThan))
{
  static_assert(cpt::concepts::GreaterEqualThan.check<T, U>(), "Expression < a >= b > is ill-formed.");
}


// logical

// logical_not
template <typename T>
constexpr void diagnostic(decltype(cpt::concepts::LogicalNot))
{
  static_assert(cpt::concepts::LogicalNot.check<T>(), "Expression < !a > is ill-formed.");
}

// logical_and
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LogicalAnd))
{
  static_assert(cpt::concepts::LogicalAnd.check<T, U>(), "Expression < a && b > is ill-formed.");
}

// logical_or
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::LogicalOr))
{
  static_assert(cpt::concepts::LogicalOr.check<T, U>(), "Expression < a || b > is ill-formed.");
}


// other

// comma
template <typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Comma))
{
  static_assert(cpt::concepts::Comma.check<T, U>(), "Expression < a, b > is ill-formed.");
}

// ternary
template <typename B, typename T, typename U = T>
constexpr void diagnostic(decltype(cpt::concepts::Ternary))
{
  static_assert(cpt::concepts::Ternary.check<B, T, U>(), "Expression < expr ? a : b > is ill-formed.");
}

// invocable
template <typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::Invocable))
{
  static_assert(cpt::concepts::Invocable.check<F, Args...>(),
                "Expression < std::invoke(func, args...) > is ill-formed.");
}

// invocable r
template <typename R, typename F, typename... Args>
constexpr void diagnostic(decltype(cpt::concepts::InvocableR))
{
  static_assert(cpt::concepts::InvocableR.check<R, F, Args...>(),
                "Expression < ret = std::invoke(func, args...) > is ill-formed.");
}

}}} // namespace cpt::utility::diagnostic

#endif // METAPROG_CPT_UTILITY_DIAGNOSTIC_HPP_
