#pragma once

#include "details/filter_indexes.hpp"

#include "unpack.hpp"

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common_helpers = blackmagic::common::helpers;

namespace details {

template <template <typename...> class Pred, typename... Us>
struct make_remove_if_indexes {
  const common_helpers::trait_t<Pred, Us...>& trait;

  constexpr make_remove_if_indexes(const common_helpers::trait_t<Pred, Us...>& t)
    : trait(t)
  {
  }

  template <typename... Ts>
  constexpr auto operator()(Ts&&... t) const
    -> filter_indexes<static_cast<bool>(!std::decay_t<decltype(trait(std::forward<Ts>(t)))>::value)...>
  {
    return {};
  }
};

template <typename Indexes, typename... Ts, size_t... I>
constexpr auto build_removed_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<Indexes::indexes[I]>(tpl)...);
}

template <template <typename...> class Pred, typename... Us, typename... Ts, size_t... I>
constexpr decltype(auto) remove_if_impl(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& trait,
                                        std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_remove_if_indexes{trait}));
  return build_removed_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

} // namespace details

struct remove_if_t {
  template <template <typename...> class Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& trait) const
  {
    return details::remove_if_impl(tpl, trait, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr remove_if_t remove_if{};

}} // namespace blackmagic::tuple::algorithm
