#pragma once

#include "../utility.hpp"
#include "front.hpp"
#include "pop_front.hpp"
#include "push_front.hpp"
#include "repeat.hpp"

#include "../../common/utility.hpp"
#include "../../integral/types.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

// fwd dcl
struct zip_t {
  template <typename... Ts>
  constexpr auto operator()(Ts&&... tpls) const;
};

inline constexpr const zip_t zip{};

namespace details {

template <typename... Ts, size_t... I>
constexpr auto zip_impl(std::index_sequence<I...>, Ts&&... tpls)
{
  if constexpr (sizeof...(I) == 0) {
    return repeat(std::tuple<>(), integral::size_t_t<sizeof...(Ts)>{});
  }
  else if constexpr (sizeof...(I) == 1) {
    return std::make_tuple(std::make_tuple(front(std::forward<Ts>(tpls))...));
  }
  else {
    return push_front(zip(pop_front(std::forward<Ts>(tpls))...), std::make_tuple(front(std::forward<Ts>(tpls))...));
  }
}

template <typename T, typename... Ts>
constexpr auto zip_impl(T&& tpl, Ts&&... tpls)
{
  return zip_impl(std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>{}, std::forward<T>(tpl),
                  std::forward<Ts>(tpls)...);
}

} // namespace details

template <typename... Ts>
constexpr auto zip_t::operator()(Ts&&... tpls) const
{
  if constexpr (sizeof...(Ts) == 0) {
    return std::tuple<>();
  }
  else {
    static_assert((is_tuple_v<std::remove_reference_t<Ts>> && ...), "Cannot zip tuple and no-tuple data-type!");
    static_assert(common::are_equal(std::tuple_size_v<std::remove_reference_t<Ts>>...),
                  "Given tuples' size are different!");

    return details::zip_impl(std::forward<Ts>(tpls)...);
  }
}

}} // namespace blackmagic::tuple::algorithm
