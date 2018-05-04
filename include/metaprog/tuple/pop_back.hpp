#pragma once

#include "../type/type.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace type = metaprog::type;

namespace details {

template <typename... Ts, size_t... I>
constexpr auto pop_back_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<I>(tpl)...);
}

struct pop_back_t {
  template <typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return details::pop_back_impl(
      tpl, std::make_index_sequence<type::minus<type::size_t_<sizeof...(Ts)>, type::int_<1>>::value>{});
  }
};

} // namespace details

inline constexpr details::pop_back_t pop_back{};

}} // namespace metaprog::tuple::algorithm
