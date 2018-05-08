#pragma once

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace type = metaprog::type;

struct back_t {
  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return std::get<(sizeof...(Ts) - 1)>(tpl);
  }
};

inline constexpr back_t back{};

}} // namespace blackmagic::tuple::algorithm
