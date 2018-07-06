#pragma once

#include "back.hpp"
#include "pop_back.hpp"
#include "push_front.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, std::size_t N, typename Ret = basic_type_list<>, typename = void>
struct take_back {
};

template <typename List, std::size_t N, typename Ret>
struct take_back<List, N, Ret, std::enable_if_t<(N > List::size())>> {
  static_assert(common::dependent_false_v<List>, "Cannot take more element than there are in the List!");
};

template <typename List, std::size_t N, typename Ret>
struct take_back<List, N, Ret, std::enable_if_t<(List::size() == 0 || N == 0)>> {
  using type = Ret;
};

template <typename List, std::size_t N, typename Ret>
struct take_back<List, N, Ret, std::enable_if_t<(N > 0)>>
  : take_back<pop_back_t<List>, (N - 1), push_front_t<Ret, back_t<List>>> {
};

template <typename List, std::size_t N>
using take_back_t = typename take_back<List, N>::type;

// static_assert(std::is_same_v<type_list<long, long long, double>,
//               take_back_t<type_list<char, short, float, int, long, long long, double>, 3>>);

}} // namespace blackmagic::type::algorithm
