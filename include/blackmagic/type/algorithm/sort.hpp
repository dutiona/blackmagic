#pragma once

#include "merge.hpp"
#include "take_front.hpp"
#include "take_front_from.hpp"

#include "../list.hpp"

#include "../../common/sizeof.hpp"

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

template <typename List, template <typename, typename> class Pred = common::sizeof_less, typename = void>
struct sort {
};

template <typename List, template <typename, typename> class Pred>
struct sort<List, Pred, std::enable_if_t<(List::size() < 2)>> {
  using type = List;
};

template <typename List, template <typename, typename> class Pred>
struct sort<List, Pred, std::enable_if_t<(List::size() > 1)>> {
  static constexpr auto _pivot = List::size() / 2; // Split the list in two parts
  using type =
    merge_t<basic_type_list<                                         // Recursive call on the 2 parts of the list
              typename sort<take_front_t<List, _pivot>, Pred>::type, // First half of the list
              typename sort<take_front_from_t<List, _pivot, (List::size() - _pivot)>, Pred>::type // Second half of the
                                                                                                  // type list
              >,
            Pred>;
};

template <typename List, template <typename, typename> class Pred = common::sizeof_less>
using sort_t = typename sort<List, Pred>::type;

// static_assert(std::is_same_v<type_list<char, short, int, long>, sort_t<type_list<long, int, short, char>>>);

}} // namespace blackmagic::type::algorithm
