#pragma once

#include "../common/common.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace blackmagic::tuple { inline namespace utility {

namespace common = blackmagic::common;

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
using tuple_remove_cvref = std::tuple<common::remove_cvref_t<Ts>...>;


// tuple_decay
template <typename... Ts>
using tuple_decay = std::tuple<std::decay_t<Ts>...>;


// is_tuple
template <typename T>
struct is_tuple : common::is_instantiation_of<std::tuple, T> {
};

template <typename T>
inline constexpr auto is_tuple_v = is_tuple<T>::value;

}} // namespace blackmagic::tuple::utility