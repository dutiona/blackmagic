#pragma once

#ifndef CONCEPTS_TRAITS_UTILIY_HPP_
#define CONCEPTS_TRAITS_UTILIY_HPP_

#include <type_traits>

namespace traits { namespace utility { namespace details {

// member access

// is_dereferenceable expression
template <typename T>
using _is_dereferenceable_expr = decltype(*std::declval<T>());
template <typename T>
constexpr bool _is_dereferenceable_expr_nothrow_v = noexcept(*std::declval<T>());
// is_dereferenceable
template <typename T, typename = void>
struct is_dereferenceable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_dereferenceable_impl<T, std::void_t<_is_dereferenceable_expr<T>>> : std::true_type {
};
// is_nothrow_dereferenceable
template <typename T, typename Valid = void, typename Noexcept = void>
struct is_nothrow_dereferenceable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename Valid>
struct is_nothrow_dereferenceable_impl<T, Valid, std::enable_if_t<_is_dereferenceable_expr_nothrow_v<T>>>
  : is_dereferenceable_impl<T, Valid> {
};

// is_address_of
template <typename T, typename = void>
struct is_address_of_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_address_of_impl<T, std::void_t<decltype(&std::declval<T>())>> : std::true_type {
};

// is_subscript
template <typename T, typename I, typename = void>
struct is_subscript_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename I>
struct is_subscript_impl<T, I, std::void_t<decltype(std::declval<T>()[std::declval<I>()])>> : std::true_type {
};


// assignement

// is_assignable
template <typename T, typename U = T, typename = void>
struct is_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() = std::declval<U>())>> : std::true_type {
};

// is_plus_assignable
template <typename T, typename U = T, typename = void>
struct is_plus_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_plus_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() += std::declval<U>())>> : std::true_type {
};

// is_less_assignable
template <typename T, typename U = T, typename = void>
struct is_less_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_less_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() -= std::declval<U>())>> : std::true_type {
};

// is_mult_assignable
template <typename T, typename U = T, typename = void>
struct is_mult_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mult_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() *= std::declval<U>())>> : std::true_type {
};

// is_div_assignable
template <typename T, typename U = T, typename = void>
struct is_div_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_div_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() /= std::declval<U>())>> : std::true_type {
};

// is_mod_assignable
template <typename T, typename U = T, typename = void>
struct is_mod_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_mod_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() %= std::declval<U>())>> : std::true_type {
};

// is_or_assignable
template <typename T, typename U = T, typename = void>
struct is_or_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_or_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() &= std::declval<U>())>> : std::true_type {
};

// is_and_assignable
template <typename T, typename U = T, typename = void>
struct is_and_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_and_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() &= std::declval<U>())>> : std::true_type {
};

// is_xor_assignable
template <typename T, typename U = T, typename = void>
struct is_xor_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_xor_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() ^= std::declval<U>())>> : std::true_type {
};

// is_lshift_assignable
template <typename T, typename U = T, typename = void>
struct is_lshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_lshift_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() <<= std::declval<U>())>>
  : std::true_type {
};

// is_rshift_assignable
template <typename T, typename U = T, typename = void>
struct is_rshift_assignable_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_rshift_assignable_impl<T, U, std::void_t<decltype(std::declval<T>() >>= std::declval<U>())>>
  : std::true_type {
};


// arithmetic

// is_positive
template <typename T, typename = void>
struct is_positive_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_positive_impl<T, std::void_t<decltype(+std::declval<T>())>> : std::true_type {
};

// is_negative
template <typename T, typename = void>
struct is_negative_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_negative_impl<T, std::void_t<decltype(-std::declval<T>())>> : std::true_type {
};

// is_not
template <typename T, typename = void>
struct is_not_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T>
struct is_not_impl<T, std::void_t<decltype(~std::declval<T>())>> : std::true_type {
};

// is_plus
template <typename T, typename U = T, typename = void>
struct is_plus_impl : std::false_type {
  // TODO add explicit error message via static assert HERE
};
template <typename T, typename U>
struct is_plus_impl<T, U, std::void_t<decltype(std::declval<T>() + std::declval<U>())>> : std::true_type {
};

// is_less
// is_mult
// is_div
// is_mod
// is_and
// is_or
// is_xor
// is_lshift
// is_rshift

template <typename T, typename U = T>
using less_t = decltype(std::declval<T>() - std::declval<U>()); // a - b

template <typename T, typename U = T>
using mult_t = decltype(std::declval<T>() * std::declval<U>()); // a * b

template <typename T, typename U = T>
using div_t = decltype(std::declval<T>() / std::declval<U>()); // a / b

template <typename T, typename U = T>
using mod_t = decltype(std::declval<T>() % std::declval<U>()); // a % b

template <typename T, typename U = T>
using and_t = decltype(std::declval<T>() & std::declval<U>()); // a & b

template <typename T, typename U = T>
using or_t = decltype(std::declval<T>() | std::declval<U>()); // a | b

template <typename T, typename U = T>
using xor_t = decltype(std::declval<T>() ^ std::declval<U>()); // a ^ b

template <typename T, typename U = T>
using lshift_t = decltype(std::declval<T>() << std::declval<U>()); // a << b

template <typename T, typename U = T>
using rshift_t = decltype(std::declval<T>() >> std::declval<U>()); // a >> b


// increment / decrement

template <typename T>
using pre_incrementable_t = decltype(++std::declval<T>()); // ++a

template <typename T>
using post_incrementable_t = decltype(std::declval<T>()++); // a++

template <typename T>
using pre_decrementable_t = decltype(--std::declval<T>()); // --a

template <typename T>
using post_decrementable_t = decltype(std::declval<T>()--); // a--


// comparison

template <typename T, typename U = T>
using equality_t = decltype(std::declval<T>() == std::declval<U>()); // a == b

template <typename T, typename U = T>
using inequality_t = decltype(std::declval<T>() != std::declval<U>()); // a != b

template <typename T, typename U = T>
using less_than_t = decltype(std::declval<T>() < std::declval<U>()); // a < b

template <typename T, typename U = T>
using less_equal_than_t = decltype(std::declval<T>() <= std::declval<U>()); // a <= b

template <typename T, typename U = T>
using greater_than_t = decltype(std::declval<T>() > std::declval<U>()); // a > b

template <typename T, typename U = T>
using greater_equal_than_t = decltype(std::declval<T>() >= std::declval<U>()); // a >= b


// other

template <typename T, typename... Args>
using function_call_t = decltype(std::declval<T>()(std::declval<Args>()...)); // a(args...)

}}} // namespace traits::utility::details


#endif // CONCEPTS_TRAITS_UTILIY_HPP_