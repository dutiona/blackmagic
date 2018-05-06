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
  const common_helpers::trait_t<Pred, Us...>& trait;

  constexpr make_filter_indexes(const common_helpers::trait_t<Pred, Us...>& t)
    : trait(t)
  {
  }

  template <typename... Ts>
  constexpr auto operator()(Ts&&... t) const
    -> filter_indexes<static_cast<bool>(std::decay_t<decltype(trait(std::forward<Ts>(t)))>::value)...>
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
constexpr decltype(auto) copy_if_impl(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& trait,
                                      std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_filter_indexes{trait}));
  return build_filtered_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

} // namespace details

struct copy_if_t {
  template <template <typename...> class Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const common_helpers::trait_t<Pred, Us...>& trait) const
  {
    return details::copy_if_impl(tpl, trait, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr copy_if_t copy_if{};

}} // namespace metaprog::tuple::algorithm
