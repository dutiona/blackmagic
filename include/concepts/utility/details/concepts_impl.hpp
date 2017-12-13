#pragma once

#ifndef CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
#define CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_

//#include <concepts/utility/traits.hpp>
#include "../traits.hpp"

#include <type_traits>

namespace concepts { namespace utility { namespace details {

namespace traits = traits::utility;

// member access

// indirection
template <bool SilentFailure, typename T, typename = void>
struct indirection_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the indirection concept.");
};
template <bool SilentFailure, typename T>
struct indirection_impl<
  SilentFailure, T, std::enable_if_t<std::disjunction_v<traits::is_indirection<T>, traits::is_nothrow_indirection<T>>>>
  : std::true_type {
};

// address_of
template <bool SilentFailure, typename T, typename = void>
struct address_of_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the address_of concept.");
};
template <bool SilentFailure, typename T>
struct address_of_impl<SilentFailure, T,
                       std::enable_if_t<std::disjunction_v<traits::is_address_of<T>, traits::is_nothrow_address_of<T>>>>
  : std::true_type {
};

// subscript
template <bool SilentFailure, typename T, typename I, typename = void>
struct subscript_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the subscript concept.");
};
template <bool SilentFailure, typename T, typename I>
struct subscript_impl<
  SilentFailure, T, I,
  std::enable_if_t<std::disjunction_v<traits::is_subscript<T, I>, traits::is_nothrow_subscript<T, I>>>>
  : std::true_type {
};

// pointer_to_member_of_object
template <bool SilentFailure, typename T, typename I, typename = void>
struct pointer_to_member_of_object_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the pointer_to_member_of_object concept.");
};
template <bool SilentFailure, typename T, typename I>
struct pointer_to_member_of_object_impl<
  SilentFailure, T, I,
  std::enable_if_t<std::disjunction_v<traits::is_pointer_to_member_of_object<T, I>,
                                      traits::is_nothrow_pointer_to_member_of_object<T, I>>>> : std::true_type {
};

// pointer_to_member_of_pointer
template <bool SilentFailure, typename T, typename I, typename = void>
struct pointer_to_member_of_pointer_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the pointer_to_member_of_pointer concept.");
};
template <bool SilentFailure, typename T, typename I>
struct pointer_to_member_of_pointer_impl<
  SilentFailure, T, I,
  std::enable_if_t<std::disjunction_v<traits::is_pointer_to_member_of_pointer<T, I>,
                                      traits::is_nothrow_pointer_to_member_of_pointer<T, I>>>> : std::true_type {
};


// assignement

// assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_assignable<T, U>, traits::is_nothrow_assignable<T, U>>>>
  : std::true_type {
};

// plus_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct plus_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the plus_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct plus_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_plus_assignable<T, U>, traits::is_nothrow_plus_assignable<T, U>>>>
  : std::true_type {
};

// less_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct less_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the less_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct less_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_less_assignable<T, U>, traits::is_nothrow_less_assignable<T, U>>>>
  : std::true_type {
};

// mult_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct mult_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the mult_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct mult_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_mult_assignable<T, U>, traits::is_nothrow_mult_assignable<T, U>>>>
  : std::true_type {
};

// div_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct div_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the div_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct div_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_div_assignable<T, U>, traits::is_nothrow_div_assignable<T, U>>>>
  : std::true_type {
};

// mod_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct mod_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the mod_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct mod_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_mod_assignable<T, U>, traits::is_nothrow_mod_assignable<T, U>>>>
  : std::true_type {
};

// or_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct or_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the or_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct or_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_or_assignable<T, U>, traits::is_nothrow_or_assignable<T, U>>>>
  : std::true_type {
};

// and_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct and_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the and_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct and_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_and_assignable<T, U>, traits::is_nothrow_and_assignable<T, U>>>>
  : std::true_type {
};

// xor_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct xor_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the xor_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct xor_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_xor_assignable<T, U>, traits::is_nothrow_xor_assignable<T, U>>>>
  : std::true_type {
};

// lshift_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct lshift_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the lshift_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct lshift_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_lshift_assignable<T, U>, traits::is_nothrow_lshift_assignable<T, U>>>>
  : std::true_type {
};

// rshift_assignable
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct rshift_assignable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the rshift_assignable concept.");
};
template <bool SilentFailure, typename T, typename U>
struct rshift_assignable_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_rshift_assignable<T, U>, traits::is_nothrow_rshift_assignable<T, U>>>>
  : std::true_type {
};


// arithmetic

// positive
template <bool SilentFailure, typename T, typename = void>
struct positive_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the positive concept.");
};
template <bool SilentFailure, typename T>
struct positive_impl<SilentFailure, T,
                     std::enable_if_t<std::disjunction_v<traits::is_positive<T>, traits::is_nothrow_positive<T>>>>
  : std::true_type {
};

// negative
template <bool SilentFailure, typename T, typename = void>
struct negative_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the negative concept.");
};
template <bool SilentFailure, typename T>
struct negative_impl<SilentFailure, T,
                     std::enable_if_t<std::disjunction_v<traits::is_negative<T>, traits::is_nothrow_negative<T>>>>
  : std::true_type {
};

// not
template <bool SilentFailure, typename T, typename = void>
struct not_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the not concept.");
};
template <bool SilentFailure, typename T>
struct not_impl<SilentFailure, T, std::enable_if_t<std::disjunction_v<traits::is_not<T>, traits::is_nothrow_not<T>>>>
  : std::true_type {
};

// plus
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct plus_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the plus concept.");
};
template <bool SilentFailure, typename T, typename U>
struct plus_impl<SilentFailure, T, U,
                 std::enable_if_t<std::disjunction_v<traits::is_plus<T, U>, traits::is_nothrow_plus<T, U>>>>
  : std::true_type {
};

// less
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct less_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the less concept.");
};
template <bool SilentFailure, typename T, typename U>
struct less_impl<SilentFailure, T, U,
                 std::enable_if_t<std::disjunction_v<traits::is_less<T, U>, traits::is_nothrow_less<T, U>>>>
  : std::true_type {
};

// mult
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct mult_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the mult concept.");
};
template <bool SilentFailure, typename T, typename U>
struct mult_impl<SilentFailure, T, U,
                 std::enable_if_t<std::disjunction_v<traits::is_mult<T, U>, traits::is_nothrow_mult<T, U>>>>
  : std::true_type {
};

// div
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct div_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the div concept.");
};
template <bool SilentFailure, typename T, typename U>
struct div_impl<SilentFailure, T, U,
                std::enable_if_t<std::disjunction_v<traits::is_div<T, U>, traits::is_nothrow_div<T, U>>>>
  : std::true_type {
};

// mod
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct mod_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the mod concept.");
};
template <bool SilentFailure, typename T, typename U>
struct mod_impl<SilentFailure, T, U,
                std::enable_if_t<std::disjunction_v<traits::is_mod<T, U>, traits::is_nothrow_mod<T, U>>>>
  : std::true_type {
};

// and
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct and_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the and concept.");
};
template <bool SilentFailure, typename T, typename U>
struct and_impl<SilentFailure, T, U,
                std::enable_if_t<std::disjunction_v<traits::is_and<T, U>, traits::is_nothrow_and<T, U>>>>
  : std::true_type {
};

// or
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct or_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the or concept.");
};
template <bool SilentFailure, typename T, typename U>
struct or_impl<SilentFailure, T, U,
               std::enable_if_t<std::disjunction_v<traits::is_or<T, U>, traits::is_nothrow_or<T, U>>>>
  : std::true_type {
};

// xor
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct xor_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the xor concept.");
};
template <bool SilentFailure, typename T, typename U>
struct xor_impl<SilentFailure, T, U,
                std::enable_if_t<std::disjunction_v<traits::is_xor<T, U>, traits::is_nothrow_xor<T, U>>>>
  : std::true_type {
};

// lshift
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct lshift_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the lshift concept.");
};
template <bool SilentFailure, typename T, typename U>
struct lshift_impl<SilentFailure, T, U,
                   std::enable_if_t<std::disjunction_v<traits::is_lshift<T, U>, traits::is_nothrow_lshift<T, U>>>>
  : std::true_type {
};

// rshift
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct rshift_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the rshift concept.");
};
template <bool SilentFailure, typename T, typename U>
struct rshift_impl<SilentFailure, T, U,
                   std::enable_if_t<std::disjunction_v<traits::is_rshift<T, U>, traits::is_nothrow_rshift<T, U>>>>
  : std::true_type {
};


// increment / decrement

// pre_incrementable
template <bool SilentFailure, typename T, typename = void>
struct pre_incrementable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the pre_incrementable concept.");
};
template <bool SilentFailure, typename T>
struct pre_incrementable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_pre_incrementable<T>, traits::is_nothrow_pre_incrementable<T>>>>
  : std::true_type {
};

// post_incrementable
template <bool SilentFailure, typename T, typename = void>
struct post_incrementable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the post_incrementable concept.");
};
template <bool SilentFailure, typename T>
struct post_incrementable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_post_incrementable<T>, traits::is_nothrow_post_incrementable<T>>>>
  : std::true_type {
};

// pre_decrementable
template <bool SilentFailure, typename T, typename = void>
struct pre_decrementable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the pre_decrementable concept.");
};
template <bool SilentFailure, typename T>
struct pre_decrementable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_pre_decrementable<T>, traits::is_nothrow_pre_decrementable<T>>>>
  : std::true_type {
};

// post_decrementable
template <bool SilentFailure, typename T, typename = void>
struct post_decrementable_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the post_decrementable concept.");
};
template <bool SilentFailure, typename T>
struct post_decrementable_impl<
  SilentFailure, T,
  std::enable_if_t<std::disjunction_v<traits::is_post_decrementable<T>, traits::is_nothrow_post_decrementable<T>>>>
  : std::true_type {
};


// comparison

// equality
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct equality_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the equality concept.");
};
template <bool SilentFailure, typename T, typename U>
struct equality_impl<SilentFailure, T, U,
                     std::enable_if_t<std::disjunction_v<traits::is_equality<T, U>, traits::is_nothrow_equality<T, U>>>>
  : std::true_type {
};

// inequality
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct inequality_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the inequality concept.");
};
template <bool SilentFailure, typename T, typename U>
struct inequality_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_inequality<T, U>, traits::is_nothrow_inequality<T, U>>>>
  : std::true_type {
};

// less_than
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct less_than_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the less_than concept.");
};
template <bool SilentFailure, typename T, typename U>
struct less_than_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_less_than<T, U>, traits::is_nothrow_less_than<T, U>>>>
  : std::true_type {
};

// less_equal_than
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct less_equal_than_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the less_equal_than concept.");
};
template <bool SilentFailure, typename T, typename U>
struct less_equal_than_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_less_equal_than<T, U>, traits::is_nothrow_less_equal_than<T, U>>>>
  : std::true_type {
};

// greater_than
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct greater_than_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the greater_than concept.");
};
template <bool SilentFailure, typename T, typename U>
struct greater_than_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_greater_than<T, U>, traits::is_nothrow_greater_than<T, U>>>>
  : std::true_type {
};

// greater_equal_than
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct greater_equal_than_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the greater_equal_than concept.");
};
template <bool SilentFailure, typename T, typename U>
struct greater_equal_than_impl<SilentFailure, T, U,
                               std::enable_if_t<std::disjunction_v<traits::is_greater_equal_than<T, U>,
                                                                   traits::is_nothrow_greater_equal_than<T, U>>>>
  : std::true_type {
};


// logical

// logical_not
template <bool SilentFailure, typename T, typename = void>
struct logical_not_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the logical_not concept.");
};
template <bool SilentFailure, typename T>
struct logical_not_impl<
  SilentFailure, T, std::enable_if_t<std::disjunction_v<traits::is_logical_not<T>, traits::is_nothrow_logical_not<T>>>>
  : std::true_type {
};

// logical_and
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct logical_and_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the logical_and concept.");
};
template <bool SilentFailure, typename T, typename U>
struct logical_and_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_logical_and<T, U>, traits::is_nothrow_logical_and<T, U>>>>
  : std::true_type {
};

// logical_or
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct logical_or_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the logical_or concept.");
};
template <bool SilentFailure, typename T, typename U>
struct logical_or_impl<
  SilentFailure, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_logical_or<T, U>, traits::is_nothrow_logical_or<T, U>>>>
  : std::true_type {
};


// other

// comma
template <bool SilentFailure, typename T, typename U = T, typename = void>
struct comma_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the comma concept.");
};
template <bool SilentFailure, typename T, typename U>
struct comma_impl<SilentFailure, T, U,
                  std::enable_if_t<std::disjunction_v<traits::is_comma<T, U>, traits::is_nothrow_comma<T, U>>>>
  : std::true_type {
};

// ternary
template <bool SilentFailure, typename B, typename T, typename U = T, typename = void>
struct ternary_impl : std::false_type {
  static_assert(SilentFailure, "Given types fail to model the ternary concept.");
};
template <bool SilentFailure, typename B, typename T, typename U>
struct ternary_impl<
  SilentFailure, B, T, U,
  std::enable_if_t<std::disjunction_v<traits::is_ternary<B, T, U>, traits::is_nothrow_ternary<B, T, U>>>>
  : std::true_type {
};

// invocable
using traits::details::_holder;
template <bool SilentFailure, typename Holder, typename = void>
struct invocable_impl : std::false_type {
  static_assert(SilentFailure, "Holder<F, Args...> fails to model the invocable concept.");
};
template <bool SilentFailure, template <typename F, typename... Args> typename Holder, typename F, typename... Args>
struct invocable_impl<
  SilentFailure, Holder<F, Args...>,
  std::enable_if_t<std::disjunction_v<traits::is_invocable<F, Args...>, traits::is_nothrow_invocable<F, Args...>>>>
  : std::true_type {
};

// invocable r
using traits::details::_holder_r;
template <bool SilentFailure, typename Holder, typename = void>
struct invocable_r_impl : std::false_type {
  static_assert(SilentFailure, "Holder<R, F, Args...> fails to model the invocable_r concept.");
};
template <bool SilentFailure, template <typename R, typename F, typename... Args> typename Holder, typename R,
          typename F, typename... Args>
struct invocable_r_impl<SilentFailure, Holder<R, F, Args...>,
                        std::enable_if_t<std::disjunction_v<traits::is_invocable_r<R, F, Args...>,
                                                            traits::is_nothrow_invocable_r<R, F, Args...>>>>
  : std::true_type {
};

}}} // namespace concepts::utility::details


#endif // CONCEPTS_UTILIY_DETAILS_CONCEPTS_IMPL_HPP_
