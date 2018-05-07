#pragma once

#include "replace_if.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

struct replace_t {
  template <typename S, typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, S&& search_value, T&& replace_value) const
  {
    return replace_if(tpl, [v = search_value](auto&& e){ v == e; }, std::forward<T>(replace_value));
  }
};

inline constexpr replace_t replace{};

}} // namespace metaprog::tuple::algorithm
