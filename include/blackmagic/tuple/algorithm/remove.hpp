#pragma once

#include "remove_if.hpp"

#include "../../common/traits_ext.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace algorithm {

struct remove_t {
  template <typename T, typename... Ts>
  constexpr auto operator()(const std::tuple<Ts...>& tpl, T&& value) const
  {
    return remove_if(tpl, common::trait<std::is_same, std::decay_t<decltype(std::forward<T>(value))>>);
  }
};

inline constexpr const remove_t remove{};

}} // namespace blackmagic::tuple::algorithm
