#pragma once

#ifndef CONCEPTS_DETAILS_LIBRARY_HPP_
#define CONCEPTS_DETAILS_LIBRARY_HPP_

#include <type_traits>
#include <utility>

namespace concepts { namespace details {

template <typename T, typename Arg1, typename Arg2>
using compare_equiv_t =
  decltype(!std::declval<T>()(std::declval<Arg1>(), std::declval<Arg2>())
           && !std::declval<T>()(std::declval<Arg2>(), std::declval<Arg1>())); // !cmp(a, b) && !cmp(b, a)

template <typename T, typename... Args>
using constructible_t = decltype(T(std::declval<Args>()...)); // T(args...)

}} // namespace concepts::details

#endif // CONCEPTS_DETAILS_LIBRARY_HPP_
