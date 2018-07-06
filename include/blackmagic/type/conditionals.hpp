#pragma once

#include "helpers.hpp"

#include <type_traits>

namespace blackmagic::type {

using helpers::call_t;
using helpers::check_v;

// Conditionnal metafunc

template <bool B, typename Then, typename Else, typename = void>
struct if_ {
};

template <bool B, typename Then, typename Else>
struct if_<B, Then, Else, std::enable_if_t<B>> {
  using type = Then;
};

template <bool B, typename Then, typename Else>
struct if_<B, Then, Else, std::enable_if_t<!B>> {
  using type = Else;
};

template <bool B, typename Then, typename Else>
using if_t_ = typename if_<B, Then, Else>::type;

namespace {

template <typename T>
struct switch_impl {
  template <typename Case, typename... Cases>
  struct impl : if_t_<check_v<Case, T>, typename Case::type, typename switch_impl<T>::template impl<Cases...>> {
  };
  template <typename Case>
  struct impl<Case> : if_t_<check_v<Case, T>, typename Case::type, void> {
  };

  template <typename... Cases>
  using type = impl<Cases...>;
};

} // namespace

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
using switch_ = typename switch_impl<T>::template type<Cases...>;

} // namespace blackmagic::type
