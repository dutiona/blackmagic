#pragma once

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

struct push_front_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& e) const
  {
    return std::tuple_cat(std::make_tuple(std::forward<T>(e)), tpl);
  }
};

} // namespace details

inline constexpr details::push_front_t push_front{};

}} // namespace metaprog::tuple::algorithm
