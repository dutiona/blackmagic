#pragma once

#include "pop_back.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, std::size_t N, typename = void>
struct pop_back_n {
};

template <typename List, std::size_t N>
struct pop_back_n<List, N, std::enable_if_t<(N > List::size)>> {
  static_assert(common::dependent_false_v<List>, "Cannot pop more element than there are in the List!");
};

template <typename List, std::size_t N>
struct pop_back_n<List, N, std::enable_if_t<(N == 0)>> {
  using type = List;
};

template <typename List, std::size_t N>
struct pop_back_n<List, N, std::enable_if_t<(N > 0)>> : pop_back_n<pop_back_t<List>, (N - 1)> {
};

template <typename List, std::size_t N>
using pop_back_n_t = typename pop_back_n<List, N>::type;

// static_assert(std::is_same_v<type_list<int, double, int, int>, pop_back_n_t<type_list<int, double, int, int, double,
// float, char>, 3>>);

}} // namespace blackmagic::type::algorithm
