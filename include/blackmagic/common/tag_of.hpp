#pragma once

#include "detector.hpp"

#include <type_traits>

namespace blackmagic::common {

namespace {
template <typename T>
using special_tag_t = typename T::special_tag;
} // namespace

template <typename T, typename = void>
struct tag_of {
  using type = T;
};

template <typename T>
struct tag_of<T, std::enable_if_t<is_detected_v<special_tag_t, T>>> {
  using type = special_tag_t<T>;
};

template <typename T>
using tag_of_t = typename tag_of<T>::type;

} // namespace blackmagic::common
