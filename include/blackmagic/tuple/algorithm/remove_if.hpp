#pragma once

#include "details/filter_indexes.hpp"

#include "unpack.hpp"

#include "../../common/traits_ext.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

using common::_v;

namespace details {

template <typename Pred>
class make_remove_if_indexes {
  const Pred& pred_;

public:
  constexpr make_remove_if_indexes(const Pred& pred)
    : pred_(pred)
  {
  }

  template <typename... Ts>
  constexpr auto operator()(Ts&&... t) const
    -> filter_indexes<static_cast<bool>(!_v<std::decay_t<decltype(pred_(std::forward<Ts>(t)))>>)...>
  {
    return {};
  }
};

template <typename Indexes, typename... Ts, size_t... I>
constexpr auto build_removed_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<Indexes::indexes[I]>(tpl)...);
}

template <typename Pred, typename... Ts, size_t... I>
constexpr decltype(auto) remove_if_impl(const std::tuple<Ts...>& tpl, const Pred& pred, std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_remove_if_indexes{pred}));
  return build_removed_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}

} // namespace details

struct remove_if_t {
  template <typename Pred, typename... Us, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, const Pred& pred) const
  {
    return details::remove_if_impl(tpl, pred, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr const remove_if_t remove_if{};

}} // namespace blackmagic::tuple::algorithm
