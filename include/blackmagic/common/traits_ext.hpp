#pragma once

#include <algorithm>
#include <type_traits>

namespace blackmagic::common { inline namespace traits_ext {

// _t
template <typename T>
using _t = typename T::type;

// _v
template <typename T>
inline constexpr auto _v = T::value;

// _v_t
template <typename T>
inline constexpr auto _v_t = T::type::value;


// remove_cvref
template <typename T>
using remove_cvref = std::remove_cv<std::remove_reference_t<T>>;

template <typename T>
using remove_cvref_t = _t<remove_cvref<T>>;


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
struct partial_trait_t {
  template <typename... Args>
  using type = Pred<Us..., Args...>;

  template <typename... Args>
  constexpr auto operator()(Args...) const
  {
    return type<Args...>{};
  }
};
template <template <typename...> class Pred, typename... Us>
inline constexpr partial_trait_t<Pred, Us...> trait{};


// reverse_trait
template <template <typename...> class Pred, typename... Us>
struct reverse_partial_trait_t {
  template <typename... Args>
  using type = Pred<Args..., Us...>;

  template <typename... Args>
  constexpr auto operator()(Args...) const
  {
    return type<Args...>{};
  }
};
template <template <typename...> class Pred, typename... Us>
inline constexpr reverse_partial_trait_t<Pred, Us...> reverse_trait{};


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
struct partial_value_t {
  template <auto... Args>
  using type = Pred<Us..., Args...>;

  template <auto... Args>
  constexpr auto operator()(...) const
  {
    return type<Args...>{};
  }
};
template <template <auto...> class Pred, auto... Us>
inline constexpr partial_value_t<Pred, Us...> value{};


// reverse_value
template <template <auto...> class Pred, auto... Us>
struct reverse_partial_value_t {
  template <auto... Args>
  using type = Pred<Args..., Us...>;

  template <auto... Args>
  constexpr auto operator()(...) const
  {
    return type<Args...>{};
  }
};
template <template <auto...> class Pred, auto... Us>
inline constexpr reverse_partial_value_t<Pred, Us...> reverse_value{};

// is_instantiation_of
template <template <typename...> class Template, typename T>
struct is_instantiation_of : std::false_type {
};

template <template <typename...> class Template, typename... Args>
struct is_instantiation_of<Template, Template<Args...>> : std::true_type {
};

template <template <auto...> class Template, typename T>
struct is_valued_instantiation_of : std::false_type {
};

template <template <auto...> class Template, auto... Args>
struct is_valued_instantiation_of<Template, Template<Args...>> : std::true_type {
};


// is_swappable_with
namespace {
using std::swap;

template <typename T, typename U = T, typename = void>
struct swappable : std::false_type {
};

template <typename T, typename U>
struct swappable<T, U, std::void_t<decltype(swap(std::declval<T>(), std::declval<U>()))>> : std::true_type {
};
} // namespace

template <typename T, typename U = T>
using is_swappable_with = swappable<T, U>;

template <typename T, typename U = T>
inline constexpr auto is_swappable_with_v = is_swappable_with<T, U>::value;


// apply_if
template <bool B, template <typename> class M, typename T>
using apply_if = std::conditional<B, M<T>, T>;

template <bool B, template <typename> class M, typename T>
using apply_if_t = typename apply_if<B, M, T>::type;


// type_identity
template <typename T>
struct type_identity {
  using type = T;
};


}} // namespace blackmagic::common::traits_ext
