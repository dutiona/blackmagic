#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"
#include "remove_if.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"
#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename Ret = basic_type_list<>, typename = void>
struct unique {
};

template <typename List, typename Ret>
struct unique<List, Ret, std::enable_if_t<(List::size() == 0)>> {
  using type = Ret;
};

template <typename List, typename Ret>
struct unique<List, Ret, std::enable_if_t<(List::size() > 0)>> {
  // Make a predicate that match the current element
  template <typename T>
  using _is_current_element = typename common::partial_trait_t<std::is_same, front_t<List>>::template type<T>;
  // Recursively call unique with a first parameter where you remove all element matching the current
  // And a Ret list where you pushed back the front of List
  using type =
    typename unique<remove_if_t<pop_front_t<List>, _is_current_element>, push_back_t<Ret, front_t<List>>>::type;
};

template <typename List>
using unique_t = typename unique<List>::type;

// static_assert(std::is_same_v<type_list<int, double, float, char>, unique_t<type_list<int, double, int, float, double,
// int, char, char, float>>>);

}} // namespace blackmagic::type::algorithm
