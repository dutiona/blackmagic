#pragma once

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename = void>
struct front {
};

template <typename List>
struct front<List, std::enable_if_t<(List::size() == 0)>> {
  static_assert(common::dependent_false_v<List>, "List is empty!");
};

template <template <typename, typename...> class List, typename T, typename... Ts>
struct front<List<T, Ts...>, std::enable_if_t<(List<T, Ts...>::size() > 0)>> {
  using type = T;
};

template <typename List>
using front_t = typename front<List>::type;

// static_assert(std::is_same_v<int, front_t<type_list<int, double>>>);

}} // namespace blackmagic::type::algorithm
