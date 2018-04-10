#pragma once

#include "helpers.hpp"
#include "integral_types.hpp"
#include "type_list.hpp"

namespace metaprog::type { inline namespace algorithm {

using helpers::call_t;

namespace details {

template <typename Node>
struct at_impl {
  template <typename CurrentIndex, typename TargetIndex>
  struct type_select_ : call_t<at_impl<tail<Node>>, size_t_<CurrentIndex{} + 1>, TargetIndex> {
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
  struct type : call_t<details::at_impl<Node>, size_t_<head_index<Node>>, I> {
    static_assert(head_index<Node> <= I{}, "Requesting at from a node with an index further ahead. Can't go back.");
    static_assert(size<Node> >= I{}, "Overflow when calling at on Node");
  };
};

template <typename Node>
struct list_at {
  template <typename I>
  using type = call_t<at<list<Node>>, I>;
};

template <typename Node>
struct end {
  using type = call_t<at<Node>, size_t_<size<Node>>>;
};

template <typename Node>
struct list_end {
  using type = call_t<end<list<Node>>>;
};


}} // namespace metaprog::type::algorithm
