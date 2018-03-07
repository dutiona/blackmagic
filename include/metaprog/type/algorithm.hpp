#pragma once

#ifndef METAPROG_TYPE_ALGORITHM_HPP
#define METAPROG_TYPE_ALGORITHM_HPP

#include "integral_types.hpp"
#include "type_list.hpp"

#include <functional>

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

template <typename MetaFunc, typename... Args>
inline constexpr auto check_v = check<MetaFunc, Args...>::value;


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


template <template <typename> class Switch>
struct case_ {
  template <typename Case>
  static constexpr bool value = Switch<Case>::value;

  template <typename Then>
  using type = Then;
};

template <template <typename> class>
struct default_ {
  template <typename>
  static constexpr bool value = true;

  template <typename Then>
  using type = Then;
};

template <template <typename> class Switch>
struct switch_ {
  template <template <typename> class Case, template <typename> class... Cases>
  struct type
    : call_t<if_<check_v<case_<Switch>, Case>>, typename case_<Switch>::template type<Case>,
             typename switch_<Switch>::template type<Cases...>> {
  };
};


namespace details {

template <typename Node>
struct at_impl {
  template <typename CurrentIndex, typename TargetIndex>
  struct type : call_t<at_impl<list::tail<Node>>, literals::size_t_<CurrentIndex{} + 1>, TargetIndex> {
  };
  template <typename TargetIndex>
  struct type<TargetIndex, TargetIndex> : Node {
  };
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
