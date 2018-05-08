#pragma once

#include "end.hpp"
#include "find.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

namespace details {

} // namespace details

struct contains_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& value) const
  {
    return find(tpl, std::forward<T>(value)) != end(tpl);
  }
};

inline constexpr contains_t contains{};

}} // namespace blackmagic::tuple::algorithm
