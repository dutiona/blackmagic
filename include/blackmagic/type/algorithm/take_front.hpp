#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, std::size_t N, typename Ret = basic_type_list<>, typename = void>
struct take_front {
};

template <typename List, std::size_t N, typename Ret>
struct take_front<List, N, Ret, std::enable_if_t<(N > List::size())>> {
  static_assert(common::dependent_false_v<List>, "Cannot take more element than there are in the List!");
};

template <typename List, std::size_t N, typename Ret>
struct take_front<List, N, Ret, std::enable_if_t<(List::size() == 0 || N == 0)>> {
  using type = Ret;
};

template <typename List, std::size_t N, typename Ret>
struct take_front<List, N, Ret, std::enable_if_t<(N > 0)>>
  : take_front<pop_front_t<List>, (N - 1), push_back_t<Ret, front_t<List>>> {
};

template <typename List, std::size_t N>
using take_front_t = typename take_front<List, N>::type;

// static_assert(std::is_same_v<type_list<char, short, float>,
//               take_front_t<type_list<char, short, float, int, long, long long, double>, 3>>);

}} // namespace blackmagic::type::algorithm
