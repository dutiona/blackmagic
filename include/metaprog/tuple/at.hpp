#pragma once

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace common_helpers = metaprog::common::helpers;

namespace details {

struct at_t {
  template <typename... Ts, typename N>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl, N) const
  {
    static_assert(std::is_base_of_v<std::integral_constant, common_helpers::remove_cvref_t<N>>,
                  "Index must be an integral constant!");
    static_assert(N::value < sizeof...(Ts) && N::value >= 0, "Index out of range!");

    return std::get<N::value>(tpl);
  }
};

} // namespace details

inline constexpr details::at_t at{};

}} // namespace metaprog::tuple::algorithm
