#pragma once

#ifndef METAPROG_TYPE_ALGORITHM_HPP
#define METAPROG_TYPE_ALGORITHM_HPP

#include "integral_types.hpp"
#include "type_list.hpp"

namespace type {

namespace details {

template <typename Node, size_t CurrentIndex, size_t TargetIndex>
struct at_impl : at_impl<tail<Node>, CurrentIndex + 1, TargetIndex> {
};

template <typename Node, size_t TargetIndex>
struct at_impl<Node, TargetIndex, TargetIndex> : Node {
};

} // namespace details

template <typename Node, size_t I>
struct at : details::at_impl<Node, head_index<Node>, I> {
  static_assert(head_index<Node> <= I, "Requesting at from a node with an index further ahead. Can't go back.");
  static_assert(size<Node> >= I, "Overflow when calling at on Node");
};

template <typename Node, size_t I>
struct list_at : at<list<Node>, I> {
};

template <typename Node>
struct end : at<Node, size<Node>> {
};

template <typename Node>
struct list_end : end<list<Node>> {
};


} // namespace type

#endif // METAPROG_TYPE_ALGORITHM_HPP
