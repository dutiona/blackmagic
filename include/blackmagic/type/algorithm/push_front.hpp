#pragma once

#include "../list.hpp"

#include "details/merge_lists.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, typename T>
struct push_front : details::merge_lists<basic_type_list<T>, List> {
};

template <typename List, typename T>
using push_front_t = typename push_front<List, T>::type;

// static_assert(std::is_same_v<type_list<int, double, float>, push_front_t<type_list<double, float>, int>>);

}} // namespace blackmagic::type::algorithm
