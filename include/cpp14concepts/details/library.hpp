#pragma once

#ifndef CPP14CONCEPTS_DETAILS_LIBRARY_HPP_
#  define CPP14CONCEPTS_DETAILS_LIBRARY_HPP_

#  include <type_traits>
#  include <utility>

namespace cpp14concepts { namespace details {

template <typename T, typename Arg1, typename Arg2>
using compare_equiv_t =
  decltype(!std::declval<T>()(std::declval<Arg1>(), std::declval<Arg2>())
           && !std::declval<T>()(std::declval<Arg2>(), std::declval<Arg1>())); // !cmp(a, b) && !cmp(b, a)

template <typename T, typename... Args>
using constructible_t = decltype(T(std::declval<Args>()...)); // T(args...)

}} // namespace cpp14concepts::details

#endif // CPP14CONCEPTS_DETAILS_LIBRARY_HPP_
