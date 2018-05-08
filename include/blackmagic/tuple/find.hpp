#pragma once

#include "find_if.hpp"

#include <tuple>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

} // namespace details

struct find_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& value) const
  {
    return find_if(tpl, [v = value](auto&& e) { return v == e; });
  }
};

inline constexpr find_t find{};

}} // namespace blackmagic::tuple::algorithm
