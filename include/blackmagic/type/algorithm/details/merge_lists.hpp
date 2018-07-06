#pragma once

#include "../../list.hpp"

namespace blackmagic::type { inline namespace algorithm { namespace details {

// Merge Lists
// Merge two or more type lists together
namespace {
template <typename ListLhs, typename ListRhS>
struct merge_2_lists {
};

template <template <typename...> class ListLhs, template <typename...> class ListRhs, typename... Lhs, typename... Rhs>
struct merge_2_lists<ListLhs<Lhs...>, ListRhs<Rhs...>> {
  using type = basic_type_list<Lhs..., Rhs...>;
};

template <typename ListLhs, typename ListRhs>
using merge_2_lists_t = typename merge_2_lists<ListLhs, ListRhs>::type;

} // namespace

template <typename... Lists>
struct merge_lists {
};

template <>
struct merge_lists<> {
  using type = basic_type_list<>;
};

template <typename List>
struct merge_lists<List> {
  using type = List;
};

template <typename List0, typename List1, typename... Lists>
struct merge_lists<List0, List1, Lists...> : merge_lists<merge_2_lists_t<List0, List1>, Lists...> {
};

template <typename... Lists>
using merge_lists_t = typename merge_lists<Lists...>::type;

// static_assert(std::is_same_v<basic_type_list<int, float, double, short, char>, merge_lists_t<type_list<int>,
// basic_type_list<float, double>, basic_type_list<short, char>>>);

}}} // namespace blackmagic::type::algorithm::details
