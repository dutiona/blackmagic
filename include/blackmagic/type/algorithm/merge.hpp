#pragma once

#include "back.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

#include "../list.hpp"

#include "../../common/sizeof.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

namespace {
template <typename Lhs, typename Rhs, template <typename, typename> class Pred = common::sizeof_less,
          typename Ret = basic_type_list<>, typename = void>
struct merge_two {
};

template <typename Lhs, typename Rhs, template <typename, typename> class Pred, typename Ret>
struct merge_two<Lhs, Rhs, Pred, Ret, std::enable_if_t<(Lhs::size() == 0 && Rhs::size() == 0)>> {
  using type = Ret;
};

template <typename Lhs, typename Rhs, template <typename, typename> class Pred, typename Ret>
struct merge_two<Lhs, Rhs, Pred, Ret, std::enable_if_t<(Lhs::size() == 0 && Rhs::size() > 0)>>
  : merge_two<Lhs, pop_front_t<Rhs>, Pred, push_back_t<Ret, front_t<Rhs>>> {
};

template <typename Lhs, typename Rhs, template <typename, typename> class Pred, typename Ret>
struct merge_two<Lhs, Rhs, Pred, Ret, std::enable_if_t<(Lhs::size() > 0 && Rhs::size() == 0)>>
  : merge_two<pop_front_t<Lhs>, Rhs, Pred, push_back_t<Ret, front_t<Lhs>>> {
};

template <typename Lhs, typename Rhs, template <typename, typename> class Pred, typename Ret>
struct merge_two<Lhs, Rhs, Pred, Ret, std::enable_if_t<(Lhs::size() > 0 && Rhs::size() > 0)>>
  : std::conditional_t<Pred<front_t<Lhs>, front_t<Rhs>>::value,
                       merge_two<pop_front_t<Lhs>, Rhs, Pred, push_back_t<Ret, front_t<Lhs>>>,
                       merge_two<Lhs, pop_front_t<Rhs>, Pred, push_back_t<Ret, front_t<Rhs>>>> {
};

template <typename Lhs, typename Rhs, template <typename, typename> class Pred = common::sizeof_less>
using merge_two_t = typename merge_two<Lhs, Rhs, Pred>::type;

template <typename Lhs, typename Rhs, template <typename, typename> class Pred = common::sizeof_less>
using merge_two_stable = merge_two<Rhs, Lhs, Pred>;

template <typename Lhs, typename Rhs, template <typename, typename> class Pred = common::sizeof_less>
using merge_two_stable_t = typename merge_two_stable<Lhs, Rhs, Pred>::type;

// static_assert(std::is_same_v<type_list<char, short, float, int, long, long long, double>,
//               merge_two_stable_t<type_list<char, float, long, long long>, type_list<short, int, double>>>);

} // namespace

template <typename ListsPacked, template <typename, typename> class Pred = common::sizeof_less, typename = void>
struct merge {
};

template <template <typename...> class ListsPacked, template <typename, typename> class Pred, typename... Lists>
struct merge<ListsPacked<Lists...>, Pred, std::enable_if_t<(sizeof...(Lists) == 0)>> {
  using type = basic_type_list<>;
};

template <template <typename, typename...> class ListsPacked, template <typename, typename> class Pred, typename List0,
          typename... Lists>
struct merge<ListsPacked<List0, Lists...>, Pred, std::enable_if_t<(sizeof...(Lists) == 0)>> {
  using type = List0;
};

template <template <typename, typename, typename...> class ListsPacked, template <typename, typename> class Pred,
          typename List0, typename List1, typename... Lists>
struct merge<ListsPacked<List0, List1, Lists...>, Pred, std::enable_if_t<(sizeof...(Lists) >= 0)>>
  : merge<basic_type_list<merge_two_stable_t<List0, List1, Pred>, Lists...>, Pred> {
};

template <typename ListsPacked, template <typename, typename> class Pred = common::sizeof_less>
using merge_t = typename merge<ListsPacked, Pred>::type;

// static_assert(std::is_same_v<basic_type_list<char, short, float, int, long, long long, double>,
//                              merge_t<basic_type_list<basic_type_list<char, long>, basic_type_list<float, long long>,
//                                                      basic_type_list<short, int, double>>>>);

}} // namespace blackmagic::type::algorithm
