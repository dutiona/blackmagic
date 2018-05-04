#pragma once

#include "all_of.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

struct none_of_t {
  template <typename Func, typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl, Func&& f) const
  {
    return !all_of(tpl, std::forward<Func>(f));
  }

  template <typename... Ts>
  constexpr bool operator()(std::tuple<Ts...> tpl) const
  {
    return !all_of(tpl);
  }
};

} // namespace details

inline constexpr details::none_of_t none_of{};

}} // namespace metaprog::tuple::algorithm
