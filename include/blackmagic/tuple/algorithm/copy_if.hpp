#pragma once

#include "details/filter_indexes.hpp"

#include "unpack.hpp"

#include "../../common/common.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace common = blackmagic::common;

namespace details {

template <template <typename...> class Pred, typename... Us>
class make_filter_indexes {
  const common::trait_t<Pred, Us...>& trait_;
public:
  constexpr make_filter_indexes(const common::trait_t<Pred, Us...>& t)
    : trait_(t)
  {
  }

  template <typename... Ts>
  constexpr auto operator()(Ts&&... t) const
    -> filter_indexes<static_cast<bool>(std::decay_t<decltype(trait_(std::forward<Ts>(t)))>::value)...>
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
constexpr decltype(auto) copy_if_impl(const std::tuple<Ts...>& tpl, const common::trait_t<Pred, Us...>& trait,
                                      std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_filter_indexes{trait}));
  return build_filtered_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

} // namespace details

struct copy_if_t {
  template <template <typename...> class Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const common::trait_t<Pred, Us...>& trait) const
  {
    return details::copy_if_impl(tpl, trait, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr copy_if_t copy_if{};

}} // namespace blackmagic::tuple::algorithm
