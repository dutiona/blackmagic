#pragma once

#include "../integral/types.hpp"

#include <tuple>
#include <utility>

namespace blackmagic::functional {

namespace integral = blackmagic::integral;

struct arg_t {
  template <size_t N, typename... Args>
  constexpr decltype(auto) operator()(integral::size_t_<N>, Args&&... args) const
  {
    static_assert(N < sizeof...(Args), "Argument index out of range!");

    return std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
  }
};

inline constexpr const arg_t arg{};

} // namespace blackmagic::functional
