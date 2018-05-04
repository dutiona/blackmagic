#pragma once

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

struct push_back_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& e) const
  {
    return std::tuple_cat(tpl, std::make_tuple(std::forward<T>(e)));
  }
};

} // namespace details

inline constexpr details::push_back_t push_back{};

}} // namespace metaprog::tuple::algorithm
