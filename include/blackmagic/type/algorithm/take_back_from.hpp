#pragma once

#include "pop_back.hpp"
#include "take_back.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, std::size_t I, std::size_t N>
struct take_back_from : take_back<pop_back_n_t<List, I>, N> {
};

template <typename List, std::size_t I, std::size_t N>
using take_back_from_t = typename take_back_from<List, I, N>::type;

// static_assert(std::is_same_v<type_list<float, int, long>,
//               take_back_from_t<type_list<char, short, float, int, long, long long, double>, 2, 3>>);

}} // namespace blackmagic::type::algorithm
