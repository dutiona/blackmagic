#pragma once

#include "helpers.hpp"
#include "integral_types.hpp"

namespace metaprog::type {

using helpers::call_t;
using helpers::check_v;

// Conditionnal metafunc

template <bool B>
struct if_ {
  template <typename If, typename Else>
  using type = If;
};

template <>
struct if_<false> {
  template <typename If, typename Else>
  using type = Else;
};

// gcc bug : ambiguity between inline namespace and namespace
#if (defined __GNUC__ || defined __MINGW32__) && !defined __clang__
inline namespace details {
#else
namespace details {
#endif

template <typename T>
struct switch_impl {
  template <typename Case, typename... Cases>
  struct impl : call_t<if_<check_v<Case, T>>, typename Case::type, typename switch_impl<T>::template impl<Cases...>> {
  };
  template <typename Case>
  struct impl<Case> : call_t<if_<check_v<Case, T>>, typename Case::type, void> {
  };

  template <typename... Cases>
  using type = impl<Cases...>;
};

} // namespace details

template <typename Case, typename Then>
struct case_ {
  template <typename Switch>
  static constexpr bool value = Case::template value<Switch>;

  using type = Then;
};

template <typename Then>
struct default_ {
  template <typename Switch>
  static constexpr bool value = true;

  using type = Then;
};

template <typename T, typename... Cases>
// gcc bug : ambiguity between inline namespace and namespace
#if (defined __GNUC__ || defined __MINGW32__) && !defined __clang__
using switch_ = typename switch_impl<T>::template type<Cases...>;
#else
using switch_ = typename details::switch_impl<T>::template type<Cases...>;
#endif

} // namespace metaprog::type
