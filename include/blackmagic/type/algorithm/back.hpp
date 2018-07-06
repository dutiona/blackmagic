#pragma once

#include "pop_front.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename = void>
struct back {
};

template <typename List>
struct back<List, std::enable_if_t<(List::size() == 0)>> {
  static_assert(common::dependent_false_v<List>, "List is empty!");
};

template <typename List>
struct back<List, std::enable_if_t<(List::size() > 1)>> : back<pop_front_t<List>> {
};

template <template <typename, typename...> class List, typename T, typename... Ts>
struct back<List<T, Ts...>, std::enable_if_t<(List<T, Ts...>::size() == 1)>> {
  using type = T;
};

template <typename List>
using back_t = typename back<List>::type;

// static_assert(std::is_same_v<float, back_t<type_list<char, int, double, float>>>);

}} // namespace blackmagic::type::algorithm
