#pragma once

#ifndef METAPROG_TYPE_TYPE_LIST_HPP
#define METAPROG_TYPE_TYPE_LIST_HPP

#include "integral_types.hpp"

#include <utility>

namespace metaprog::type {

template <size_t I, typename T>
struct type_item {
  static constexpr auto index = I;
  using type                  = T;
};

template <template <size_t, typename> class Lhs, size_t LhsI, typename LhsT, //
          template <size_t, typename> class Rhs, size_t RhsI, typename RhsT>
constexpr bool operator==(Lhs<LhsI, LhsT>, Rhs<RhsI, RhsT>)
{
  return LhsI == RhsI && std::is_same_v<LhsT, RhsT>;
}

template <size_t I, size_t S, typename T, typename... Ts>
struct type_list_node {
  using head                      = type_item<S - I, T>;
  using tail                      = type_list_node<I - 1, S, Ts...>;
  static constexpr auto list_size = S;
  static constexpr auto tail_size = sizeof...(Ts);
};

template <size_t S, typename T>
struct type_list_node<1, S, T> {
  using head                      = type_item<S - 1, T>;
  using tail                      = type_list_node<S - S, S, void>;
  static constexpr auto list_size = S;
  static constexpr auto tail_size = 1;
};

template <size_t S>
struct type_list_node<0, S, void> {
  using head                      = type_item<S - 0, void>;
  static constexpr auto list_size = S;
  static constexpr auto tail_size = 0;
};

template <typename... Ts>
struct type_list_factory {
  static constexpr auto list_size      = sizeof...(Ts);
  static constexpr auto index_sequence = std::index_sequence_for<Ts...>{};
  using list                           = type_list_node<sizeof...(Ts), sizeof...(Ts), Ts...>;
};

template <typename Lhs, typename Rhs, template <typename, typename> class Cmp>
constexpr int compare()
{
  if constexpr (Cmp<Lhs, Rhs>() == 0)
    return 0;
  if constexpr (Cmp<Lhs, Rhs>() < 0)
    return -1;
  if constexpr (Cmp<Lhs, Rhs>() > 0)
    return 1;
}


// List Holder

template <typename List>
struct list : List::list {
};

template <typename List>
struct list_head : list<List>::head {
};

template <typename List>
struct list_tail : list<List>::tail {
};

template <typename List>
inline constexpr auto list_size = List::list_size;

template <typename List>
inline constexpr auto list_indexes = List::index_sequence;

// Type Holder

template <typename Elem>
using elem_t = typename Elem::type;

template <typename Elem>
inline constexpr auto elem_index = Elem::index;

// Node usual operations

template <typename Node>
inline constexpr auto size = Node::list_size;

template <typename Node>
inline constexpr auto tail_size = Node::tail_size;

template <typename Node>
using head = typename Node::head;

template <typename Node>
using head_t = elem_t<head<Node>>;

template <typename Node>
inline constexpr auto head_index = elem_index<head<Node>>;

template <typename Node>
using tail = typename Node::tail;

template <typename Node>
using next_head = head<tail<Node>>;

template <typename Node>
using next_head_t = head_t<tail<Node>>;

template <typename Node>
inline constexpr auto next_head_index = head_index<tail<Node>>;

} // namespace metaprog::type

#endif // METAPROG_TYPE_TYPE_LIST_HPP
