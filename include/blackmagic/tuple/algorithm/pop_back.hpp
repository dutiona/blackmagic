#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

template <typename... Ts, size_t... I>
constexpr auto pop_back_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<I>(tpl)...);
}

} // namespace details

struct pop_back_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return details::pop_back_impl(tpl, std::make_index_sequence<(sizeof...(Ts) - 1)>{});
  }
};

inline constexpr pop_back_t pop_back{};

}} // namespace blackmagic::tuple::algorithm
