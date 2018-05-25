#pragma once

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct push_back_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& e) const
  {
    return std::tuple_cat(tpl, std::make_tuple(std::forward<T>(e)));
  }
};

inline constexpr const push_back_t push_back{};

}} // namespace blackmagic::tuple::algorithm
