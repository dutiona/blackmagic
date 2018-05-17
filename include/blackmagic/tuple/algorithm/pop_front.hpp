#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

template <typename T, typename... Ts, size_t I, size_t... J>
constexpr auto pop_front_impl(const std::tuple<T, Ts...>& tpl, std::index_sequence<I, J...>)
{
  return std::make_tuple(std::get<J>(tpl)...);
}

} // namespace details

struct pop_front_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return details::pop_front_impl(tpl, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr const pop_front_t pop_front{};

}} // namespace blackmagic::tuple::algorithm
