#pragma once

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

struct front_t {
  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return std::get<0>(tpl);
  }
};

} // namespace details

inline constexpr details::front_t front{};

}} // namespace metaprog::tuple::algorithm
