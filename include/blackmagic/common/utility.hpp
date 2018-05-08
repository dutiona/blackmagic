#pragma once

#include "../type/type.hpp"

#ifdef __GLIBCXX__
#include "../cstxpr/cstxpr.hpp"
#endif // __GLIBCXX__

#include <string_view>
#include <type_traits>

namespace blackmagic::common { inline namespace utility {


// nonesuch
struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(const nonesuch&) = delete;
  void operator=(const nonesuch&) = delete;
};


// is_detected
namespace details {

template <typename Default, template <typename...> class Op, typename ParametersPack, typename = void>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <typename Default, template <typename...> class Op, template <typename...> class ParametersPack,
          typename... Args>
struct detector<Default, Op, ParametersPack<Args...>, std::void_t<Op<Args...>>> {
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <typename...> class Op, typename... Args>
using is_detected = typename details::detector<nonesuch, Op, type::basic_list<Args...>>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = typename details::detector<nonesuch, Op, type::basic_list<Args...>>::type;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = details::detector<Default, Op, type::basic_list<Args...>>;

template <template <typename...> class Op, typename... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

template <typename Expected, template <typename...> class Op, typename... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <typename Expected, template <typename...> class Op, typename... Args>
constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

template <typename To, template <typename...> class Op, typename... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template <typename To, template <typename...> class Op, typename... Args>
constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;


// remove_cvref
template <typename T>
using remove_cvref = std::remove_cv<std::remove_reference_t<T>>;

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;


// dependent false
template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool() const
  {
    return value;
  }
};

template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});


// operator==(string_view, string_view) is not cstxpr yet in libstdc++
constexpr bool equals(std::string_view lhs, std::string_view rhs)
{
#ifdef __GLIBCXX__
  return cstxpr::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
#else
  return lhs == rhs;
#endif // __GLIBCXX__
}

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


// all_of
template <bool... Bs>
struct all_of : std::conjunction<std::bool_constant<Bs>...> {
};


// any_of
template <bool... Bs>
struct any_of : std::disjunction<std::bool_constant<Bs>...> {
};


// none_of
template <bool... Bs>
struct none_of : std::conjunction<std::bool_constant<!Bs>...> {
};


// count
template <bool... Bs>
struct count : std::integral_constant<size_t, (Bs + ...)> {
};


}} // namespace blackmagic::common::utility
