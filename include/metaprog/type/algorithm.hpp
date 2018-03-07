#pragma once

#ifndef METAPROG_TYPE_ALGORITHM_HPP
#define METAPROG_TYPE_ALGORITHM_HPP

#include "integral_types.hpp"
#include "type_list.hpp"


namespace type::algorithm {

// Call metafunc

template <typename MetaFunc, typename... Args>
struct call {
  using type = typename MetaFunc::template type<Args...>;
};
template <typename MetaFunc>
struct call<MetaFunc> {
  using type = typename MetaFunc::type;
};

template <typename MetaFunc, typename... Args>
using call_t = typename call<MetaFunc, Args...>::type;

// Check metafunc

template <typename MetaFunc, typename... Args>
struct check {
  static constexpr auto value = MetaFunc::template value<Args...>;
};
template <typename MetaFunc>
struct check<MetaFunc> {
  static constexpr auto value = MetaFunc::value;
};

template <typename MetaFunc, typename... Args>
inline constexpr auto check_v = check<MetaFunc, Args...>::value;

// Trait helper
template <template <typename...> class Trait, typename... Args>
struct make_type_from_trait {
  template <typename... Params>
  using type = typename Trait<Args..., Params...>::type;
};

template <template <typename...> class Trait, typename... Args>
struct make_value_from_trait {
  template <typename... Params>
  static constexpr auto value = Trait<Args..., Params...>::value;
};

template <template <typename...> class Trait, typename... Args>
struct make_both_from_trait {
  template <typename... Params>
  using type = typename Trait<Args..., Params...>::type;

  template <typename... Params>
  static constexpr auto value = Trait<Args..., Params...>::value;
};


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

namespace details {
template <typename T>
struct switch_impl {
  template <typename Case, typename... Cases>
  struct type_select_
    : call_t<if_<check_v<Case, T>>, typename Case::type, typename switch_impl<T>::template type_select_<Cases...>> {
  };
  template <typename Case>
  struct type_select_<Case> : call_t<if_<check_v<Case, T>>, typename Case::type, void> {
  };

  template <typename... Cases>
  using type = type_select_<Cases...>;
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
using switch_ = typename details::switch_impl<T>::template type<Cases...>;

namespace details {

template <typename Node>
struct at_impl {
  template <typename CurrentIndex, typename TargetIndex>
  struct type_select_ : call_t<at_impl<list::tail<Node>>, literals::size_t_<CurrentIndex{} + 1>, TargetIndex> {
  };
  template <typename TargetIndex>
  struct type_select_<TargetIndex, TargetIndex> : Node {
  };

  template <typename CurrentIndex, typename TargetIndex>
  using type = type_select_<CurrentIndex, TargetIndex>;
};

} // namespace details

template <typename Node>
struct at {
  template <typename I>
  struct type : call_t<details::at_impl<Node>, literals::size_t_<list::head_index<Node>>, I> {
    static_assert(list::head_index<Node> <= I{},
                  "Requesting at from a node with an index further ahead. Can't go back.");
    static_assert(list::size<Node> >= I{}, "Overflow when calling at on Node");
  };
};

template <typename Node>
struct list_at {
  template <typename I>
  using type = call_t<at<list::list<Node>>, I>;
};

template <typename Node>
struct end {
  using type = call_t<at<Node>, literals::size_t_<list::size<Node>>>;
};

template <typename Node>
struct list_end {
  using type = call_t<end<list::list<Node>>>;
};


} // namespace type::algorithm

#endif // METAPROG_TYPE_ALGORITHM_HPP
