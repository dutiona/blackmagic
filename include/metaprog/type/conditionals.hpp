#pragma once

#include "helpers.hpp"
#include "integral_types.hpp"
#include "type_list.hpp"

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

inline namespace details {
template <typename T>
struct switch_impl_ {
  template <typename Case, typename... Cases>
  struct impl : call_t<if_<check_v<Case, T>>, typename Case::type, typename switch_impl_<T>::template impl<Cases...>> {
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
using switch_ = typename switch_impl_<T>::template type<Cases...>;

} // namespace metaprog::type
