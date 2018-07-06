#pragma once

#include "front.hpp"
#include "push_back.hpp"
#include "push_front.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename Ret = basic_type_list<>, typename = void>
struct pop_back {
};

template <typename List, typename Ret>
struct pop_back<List, Ret, std::enable_if_t<(List::size() == 0 && Ret::size() == 0)>> {
  static_assert(common::dependent_false_v<List>, "List is empty!");
};

template <typename List, typename Ret> // List is one element then return empty list
struct pop_back<List, Ret, std::enable_if_t<(List::size() == 1 && Ret::size() == 0)>> {
  using type = basic_type_list<>;
};

template <typename List, typename Ret> // We have poped all ellements from List except the last one
struct pop_back<List, Ret, std::enable_if_t<(List::size() == 1 && Ret::size() > 0)>> {
  using type = Ret;
};

template <typename List, typename Ret> // We push_back (to keep ordering) on Ret the front of List
                                       // and then pop_front List (recursivly)
struct pop_back<List, Ret, std::enable_if_t<(List::size() > 1)>>
  : pop_back<pop_front_t<List>, push_back_t<Ret, front_t<List>>> {
};

template <typename List>
using pop_back_t = typename pop_back<List>::type;

// static_assert(std::is_same_v<type_list<char, double, float>, pop_back_t<type_list<char, double, float, int>>>);

}} // namespace blackmagic::type::algorithm
