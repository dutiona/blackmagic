#pragma once

#include <algorithm>
#include <type_traits>
#include <utility>

namespace blackmagic::pair { inline namespace algorithm {

namespace details {

using std::swap;

template <typename T, typename U = T, typename = void>
struct swappable : std::false_type {
};

template <typename T, typename U>
struct swappable<T, U, std::void_t<decltype(swap(std::declval<T>(), std::declval<U>()))>> : std::true_type {
};

template <typename T, typename U = T>
inline constexpr auto swappable_v = swappable<T, U>::value;

} // namespace details

// from_tuple
struct flip_inplace_t {
  template <typename T, typename U>
  constexpr void operator()(std::pair<T, U>& p) const
  {
    static_assert(details::swappable_v<T, U>, "<First> and <Second> are not swappable!");

    using std::swap;
    swap(std::move(p.first), std::move(p.second));
  }
};

inline constexpr const flip_inplace_t flip_inplace{};

}} // namespace blackmagic::pair::algorithm
