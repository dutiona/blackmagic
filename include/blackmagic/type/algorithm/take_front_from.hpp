#pragma once

#include "pop_front.hpp"
#include "take_front.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, std::size_t I, std::size_t N>
struct take_front_from : take_front<pop_front_n_t<List, I>, N> {
};

template <typename List, std::size_t I, std::size_t N>
using take_front_from_t = typename take_front_from<List, I, N>::type;

// static_assert(std::is_same_v<type_list<float, int, long>,
//               take_front_from_t<type_list<char, short, float, int, long, long long, double>, 2, 3>>);

}} // namespace blackmagic::type::algorithm
