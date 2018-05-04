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
struct make_filter_indexes {
  template <typename... Ts>
  auto operator()(Ts&&...) const -> filter_indexes<static_cast<bool>(Pred<Us..., std::decay_t<Ts>>::value)...>
  {
    return {};
  }
};

template <typename Indexes, typename... Ts, size_t... I>
constexpr auto build_filtered_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<Indexes::indexes[I]>(tpl)...);
}

template <template <typename...> class Pred, typename... Us, typename... Ts, size_t... I>
constexpr decltype(auto) copy_if_impl(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>&,
                                      std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_filter_indexes<Pred, Us...>{}));
  return build_filtered_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

struct copy_if_t {
  template <template <typename...> class Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& pred_trait) const
  {
    return copy_if_impl<Pred, Us...>(tpl, pred_trait, std::index_sequence_for<Ts...>{});
  }
};

} // namespace details

inline constexpr details::copy_if_t copy_if{};

}} // namespace metaprog::tuple::algorithm
