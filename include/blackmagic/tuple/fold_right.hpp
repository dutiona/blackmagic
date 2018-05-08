#pragma once

#include "fold_left.hpp"
#include "reverse.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

struct fold_right_t {
  template <typename Func, typename... Ts, typename... Args>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args) const
  {
    return fold_left(std::tuple_cat(reverse(std::make_tuple(std::forward<Args>(args)...)), reverse(tpl)),
                     std::forward<Func>(f));
  }
};

inline constexpr fold_right_t fold_right{};

}} // namespace blackmagic::tuple::algorithm
