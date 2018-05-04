#pragma once

#include "../common/common.hpp"

#include <tuple>
#include <utility>

namespace metaprog::tuple::helpers {

namespace common_helpers = metaprog::common::helpers;

struct identity_func_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    return std::forward<T>(t);
  }
};

inline constexpr const identity_func_t identity_func{};


// tuple_remove_const
template <typename... Ts>
using tuple_remove_const = std::tuple<std::remove_const_t<Ts>...>;
// tuple_remove_volatile
template <typename... Ts>
using tuple_remove_volatile = std::tuple<std::remove_volatile_t<Ts>...>;
// tuple_remove_cv
template <typename... Ts>
using tuple_remove_cv = std::tuple<std::remove_cv_t<Ts>...>;
// tuple_remove_reference
template <typename... Ts>
using tuple_remove_reference = std::tuple<std::remove_reference_t<Ts>...>;
// tuple_remove_cvref
template <typename... Ts>
using tuple_remove_cvref = std::tuple<common_helpers::remove_cvref_t<Ts>...>;
// tuple_decay
template <typename... Ts>
using tuple_decay = std::tuple<std::decay_t<Ts>...>;

} // namespace metaprog::tuple::helpers