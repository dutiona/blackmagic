#pragma once

#include "details/filter_indexes.hpp"

#include "unpack.hpp"

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

namespace details {

template <template <typename...> class Pred, typename... Us>
struct make_remove_if_indexes {
  template <typename... Ts>
  auto operator()(Ts&&...) const -> filter_indexes<static_cast<bool>(std::negation_v<Pred<Us..., std::decay_t<Ts>>>)...>
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
constexpr decltype(auto) remove_if_impl(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>&,
                                        std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_remove_if_indexes<Pred, Us...>{}));
  return build_removed_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

struct remove_if_t {
  template <template <typename...> class Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& pred_trait) const
  {
    return remove_if_impl<Pred, Us...>(tpl, pred_trait, std::index_sequence_for<Ts...>{});
  }
};

} // namespace details

inline constexpr details::remove_if_t remove_if{};

}} // namespace metaprog::tuple::algorithm
