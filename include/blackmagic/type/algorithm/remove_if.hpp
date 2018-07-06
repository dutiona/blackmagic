#pragma once

#include "front.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"

#include "../list.hpp"

#include "../../common/dependent_false.hpp"

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, template <typename> class Pred, typename Ret = basic_type_list<>, typename = void>
struct remove_if {
};

template <typename List, template <typename> class Pred, typename Ret>
struct remove_if<List, Pred, Ret, std::enable_if_t<(List::size() == 0)>> {
  using type = Ret;
};

template <typename List, template <typename> class Pred, typename Ret>
struct remove_if<List, Pred, Ret, std::enable_if_t<(List::size() > 0)>>
  : remove_if<pop_front_t<List>, Pred,
              std::conditional_t<Pred<front_t<List>>::value,
                                 Ret, // true : remove the element (don't push_back it to the result)
                                 push_back_t<Ret, front_t<List>> // false : keep the element (push_back it to the
                                                                 // result)
                                 >> {
};

template <typename List, template <typename> class Pred>
using remove_if_t = typename remove_if<List, Pred>::type;

// template <typename T>
// using is_int = typename partial_trait<std::is_same, int>::template type<T>;
// static_assert(std::is_same_v<type_list<double, float, char>, remove_if_t<type_list<int, double, int, float, int,
// char>, is_int>>);

}} // namespace blackmagic::type::algorithm
