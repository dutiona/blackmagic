#pragma once

#include <algorithm>
#include <type_traits>

namespace blackmagic::common { inline namespace traits_ext {

// remove_cvref
template <typename T>
using remove_cvref = std::remove_cv<std::remove_reference_t<T>>;

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;


// disable_if
template <bool b, typename T = void>
using disable_if = std::enable_if<!b, T>;

template <bool b, typename T = void>
using disable_if_t = std::enable_if_t<!b, T>;


// basic_trait
template <typename Pred>
struct basic_trait_t {
  using type = Pred;

  constexpr auto operator()() const
  {
    return type{};
  }
};
template <typename Pred>
inline constexpr basic_trait_t<Pred> basic_trait{};


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


// basic_value
template <typename Pred>
struct basic_value_t {
  using type = Pred;

  constexpr auto operator()() const
  {
    return type{};
  }
};
template <typename Pred>
inline constexpr basic_value_t<Pred> basic_value{};


// value
template <template <auto...> class Pred, auto... Us>
struct value_t {
  template <auto... Args>
  using type = Pred<Us..., Args...>;

  template <auto... Args>
  constexpr auto operator()(...) const
  {
    return type<Args...>{};
  }
};
template <template <auto...> class Pred, auto... Us>
inline constexpr value_t<Pred, Us...> value{};


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
