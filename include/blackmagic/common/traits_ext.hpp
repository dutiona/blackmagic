#pragma once

#include <algorithm>
#include <type_traits>

namespace blackmagic::common { inline namespace traits_ext {

// remove_cvref
template <typename T>
using remove_cvref = std::remove_cv<std::remove_reference_t<T>>;

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;


// trait
template <template <typename...> class Pred, typename... Us>
struct trait_t {
  template <typename... Args>
  using type = Pred<Us..., Args...>;

  template <typename... Args>
  constexpr auto operator()(Args...) const
  {
    return type<Args...>{};
  }
};
template <template <typename...> class Pred, typename... Us>
inline constexpr trait_t<Pred, Us...> trait{};


// is_instantiation_of
template <template <typename...> class Template, typename T>
struct is_instantiation_of : std::false_type {
};

template <template <typename...> class Template, typename... Args>
struct is_instantiation_of<Template, Template<Args...>> : std::true_type {
};


// _t
template <typename T>
using _t = typename T::type;

// _v
template <typename T>
inline constexpr auto _v = T::value;

// _v_t
template <typename T>
inline constexpr auto _v_t = _v<_t<T>>;


// is_swappable_with
namespace details {
using std::swap;

template <typename T, typename U = T, typename = void>
struct swappable : std::false_type {
};

template <typename T, typename U>
struct swappable<T, U, std::void_t<decltype(swap(std::declval<T>(), std::declval<U>()))>> : std::true_type {
};
} // namespace details

template <typename T, typename U = T>
using is_swappable_with = details::swappable<T, U>;

template <typename T, typename U = T>
inline constexpr auto is_swappable_with_v = is_swappable_with<T, U>::value;

}} // namespace blackmagic::common::traits_ext
