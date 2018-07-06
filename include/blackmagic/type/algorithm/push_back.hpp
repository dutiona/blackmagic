#pragma once

#include "../list.hpp"

#include "details/merge_lists.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename T>
struct push_back : details::merge_lists<List, basic_type_list<T>> {
};

template <typename List, typename T>
using push_back_t = typename push_back<List, T>::type;

// static_assert(std::is_same_v<type_list<double, float, int>, push_back_t<type_list<double, float>, int>>);

}} // namespace blackmagic::type::algorithm
