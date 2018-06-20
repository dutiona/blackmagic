#pragma once

#include "../../common/traits_ext.hpp"
#include "../../type/list.hpp"

#include <type_traits>

namespace blackmagic::concepts { inline namespace utility {

using common::_t;
using common::_v;
using common::_v_t;

// Basic verification primitives
namespace details {

template <typename T, typename = void>
struct is_valid_expr_impl : std::false_type {
};

template <typename T>
struct is_valid_expr_impl<T, std::void_t<T>> : std::true_type {
};

template <typename... Constraints>
struct are_valid_exprs_impl : std::conjunction<is_valid_expr_impl<Constraints>...> {
};

template <typename Pred, typename = void>
struct is_true_impl : std::false_type {
};

template <typename Pred>
struct is_true_impl<Pred, std::enable_if_t<_v<Pred>>> : std::true_type {
};

template <typename... Preds>
struct are_true_impl : std::conjunction<is_true_impl<Preds>...> {
};

template <typename Pred>
struct is_false_impl : std::negation<is_true_impl<Pred>> {
};

template <typename... Preds>
struct are_false_impl : std::negation<are_true_impl<Preds...>> {
};

template <typename T, typename U = T, typename = void>
struct is_same_impl : std::false_type {
};

template <typename T, typename U>
struct is_same_impl<T, U, std::enable_if_t<std::is_same_v<T, U>>> : std::true_type {
};

template <typename From, typename To, typename = void>
struct is_convertible_to_impl : std::false_type {
};

template <typename From, typename To>
struct is_convertible_to_impl<From, To, std::enable_if_t<std::is_convertible_v<From, To>>> : std::true_type {
};

template <template <typename...> class Constraint, typename... Parameters>
struct is_valid_expr_ : is_valid_expr_impl<Constraint<Parameters...>> {
};

template <typename ParametersPack, typename = void, template <typename...> class... Constraints>
struct are_valid_exprs_ : std::false_type {
};

template <template <typename...> class ParametersPack, template <typename...> class... Constraints,
          typename... Parameters>
struct are_valid_exprs_<ParametersPack<Parameters...>,
                        std::enable_if_t<_v<are_valid_exprs_impl<Constraints<Parameters...>...>>>, Constraints...>
  : std::true_type {
};

template <template <typename...> class Pred, typename... Parameters>
struct is_true_ : is_true_impl<Pred<Parameters...>> {
};

template <template <auto...> class Pred, auto... Parameters>
struct is_true_v_ : is_true_impl<Pred<Parameters...>> {
};

template <typename ParametersPack, typename = void, template <typename...> class... Preds>
struct are_true_ : std::false_type {
};
template <template <typename...> class ParametersPack, template <typename...> class... Preds, typename... Parameters>
struct are_true_<ParametersPack<Parameters...>, std::enable_if_t<_v<are_true_impl<Preds<Parameters...>...>>>, Preds...>
  : std::true_type {
};

template <typename ParametersPack, typename = void, template <auto...> class... Preds>
struct are_true_v_ : std::false_type {
};
template <template <auto...> class ParametersPack, template <auto...> class... Preds, auto... Parameters>
struct are_true_v_<ParametersPack<Parameters...>, std::enable_if_t<_v<are_true_impl<Preds<Parameters...>...>>>,
                   Preds...> : std::true_type {
};

template <template <typename...> class Pred, typename... Parameters>
struct is_false_ : is_false_impl<Pred<Parameters...>> {
};

template <template <auto...> class Pred, auto... Parameters>
struct is_false_v_ : is_false_impl<Pred<Parameters...>> {
};

template <typename ParametersPack, typename = void, template <typename...> class... Preds>
struct are_false_ : std::false_type {
};
template <template <typename...> class ParametersPack, template <typename...> class... Preds, typename... Parameters>
struct are_false_<ParametersPack<Parameters...>, std::enable_if_t<_v<are_false_impl<Preds<Parameters...>...>>>,
                  Preds...> : std::true_type {
};

template <typename ParametersPack, typename = void, template <auto...> class... Preds>
struct are_false_v_ : std::false_type {
};
template <template <auto...> class ParametersPack, template <auto...> class... Preds, auto... Parameters>
struct are_false_v_<ParametersPack<Parameters...>, std::enable_if_t<_v<are_false_impl<Preds<Parameters...>...>>>,
                    Preds...> : std::true_type {
};

template <template <typename...> class T, template <typename...> class U = T, typename... Parameters>
struct is_same_ : is_same_impl<T<Parameters...>, U<Parameters...>> {
};

template <typename ParametersPack, template <typename...> class T, typename = void, template <typename...> class... U>
struct are_same_ : std::false_type {
};
template <template <typename...> class ParametersPack, template <typename...> class T,
          template <typename...> class... U, typename... Parameters>
struct are_same_<ParametersPack<Parameters...>, T,
                 std::enable_if_t<std::conjunction_v<is_same_impl<T<Parameters...>, U<Parameters...>>...>>, U...>
  : std::true_type {
};

template <template <typename...> class From, template <typename...> class To, typename... Parameters>
struct is_convertible_to_ : is_convertible_to_impl<From<Parameters...>, To<Parameters...>> {
};

template <typename ParametersPack, template <typename...> class To, typename = void,
          template <typename...> class... From>
struct are_convertible_to_ : std::false_type {
};
template <template <typename...> class ParametersPack, template <typename...> class To,
          template <typename...> class... From, typename... Parameters>
struct are_convertible_to_<
  ParametersPack<Parameters...>, To,
  std::enable_if_t<std::conjunction_v<is_convertible_to_impl<From<Parameters...>, To<Parameters...>>...>>, From...>
  : std::true_type {
};


template <template <typename...> class Constraint>
struct is_valid_expr {
  template <typename... Parameters>
  using type = is_valid_expr_<Constraint, Parameters...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class... Constraints>
struct are_valid_exprs {
  template <typename... Parameters>
  using type = are_valid_exprs_<type::basic_list<Parameters...>, void, Constraints...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class Pred>
struct is_true {
  template <typename... Parameters>
  using type = is_true_<Pred, Parameters...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <auto...> class Pred>
struct is_true_v {
  template <auto... Parameters>
  using type = is_true_v_<Pred, Parameters...>;
  template <auto... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <auto... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class... Preds>
struct are_true {
  template <typename... Parameters>
  using type = are_true_<type::basic_list<Parameters...>, void, Preds...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <auto...> class... Preds>
struct are_true_v {
  template <auto... Parameters>
  using type = are_true_v_<type::basic_value_list<Parameters...>, void, Preds...>;
  template <auto... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <auto... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class Pred>
struct is_false {
  template <typename... Parameters>
  using type = is_false_<Pred, Parameters...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <auto...> class Pred>
struct is_false_v {
  template <auto... Parameters>
  using type = is_false_v_<Pred, Parameters...>;
  template <auto... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <auto... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class... Preds>
struct are_false {
  template <typename... Parameters>
  using type = are_false_<type::basic_list<Parameters...>, void, Preds...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <auto...> class... Preds>
struct are_false_v {
  template <auto... Parameters>
  using type = are_false_v_<type::basic_value_list<Parameters...>, void, Preds...>;
  template <auto... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <auto... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class T, template <typename...> class U = T>
struct is_same {
  template <typename... Parameters>
  using type = is_same_<T, U, Parameters...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class T, template <typename...> class... U>
struct are_same {
  template <typename... Parameters>
  using type = are_same_<type::basic_list<Parameters...>, T, void, U...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class From, template <typename...> class To>
struct is_convertible_to {
  template <typename... Parameters>
  using type = is_convertible_to_<From, To, Parameters...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

template <template <typename...> class To, template <typename...> class... From>
struct are_convertible_to {
  template <typename... Parameters>
  using type = are_convertible_to_<type::basic_list<Parameters...>, To, void, From...>;
  template <typename... Parameters>
  using underlying_type = _t<type<Parameters...>>;
  template <typename... Parameters>
  static constexpr bool value = _v<type<Parameters...>>;
};

} // namespace details

template <template <typename...> class Constraint>
constexpr decltype(auto) is_valid_expr(std::string_view concept_name)
{
  return make_concept_item<details::is_valid_expr<Constraint>>(concept_name);
}

template <template <typename...> class... Constraints>
constexpr decltype(auto) are_valid_exprs(std::string_view concept_name)
{
  return make_concept_item<details::are_valid_exprs<Constraints...>>(concept_name);
}

template <template <typename...> class Pred>
constexpr decltype(auto) is_true(std::string_view concept_name)
{
  return make_concept_item<details::is_true<Pred>>(concept_name);
}

template <template <auto...> class Pred>
constexpr decltype(auto) is_true_v(std::string_view concept_name)
{
  return make_concept_item<details::is_true_v<Pred>>(concept_name);
}

template <template <typename...> class... Preds>
constexpr decltype(auto) are_true(std::string_view concept_name)
{
  return make_concept_item<details::are_true<Preds...>>(concept_name);
}

template <template <auto...> class... Preds>
constexpr decltype(auto) are_true_v(std::string_view concept_name)
{
  return make_concept_item<details::are_true_v<Preds...>>(concept_name);
}

template <template <typename...> class Pred>
constexpr decltype(auto) is_false(std::string_view concept_name)
{
  return make_concept_item<details::is_false<Pred>>(concept_name);
}

template <template <auto...> class Pred>
constexpr decltype(auto) is_false_v(std::string_view concept_name)
{
  return make_concept_item<details::is_false_v<Pred>>(concept_name);
}

template <template <typename...> class... Preds>
constexpr decltype(auto) are_false(std::string_view concept_name)
{
  return make_concept_item<details::are_false<Preds...>>(concept_name);
}

template <template <auto...> class... Preds>
constexpr decltype(auto) are_false_v(std::string_view concept_name)
{
  return make_concept_item<details::are_false_v<Preds...>>(concept_name);
}

template <template <typename...> class T, template <typename...> class U = T>
constexpr decltype(auto) is_same(std::string_view concept_name)
{
  return make_concept_item<details::is_same<T, U>>(concept_name);
}

template <template <typename...> class T, template <typename...> class... U>
constexpr decltype(auto) are_same(std::string_view concept_name)
{
  return make_concept_item<details::are_same<T, U...>>(concept_name);
}

template <template <typename...> class From, template <typename...> class To>
constexpr decltype(auto) is_convertible_to(std::string_view concept_name)
{
  return make_concept_item<details::is_convertible_to<From, To>>(concept_name);
}

template <template <typename...> class To, template <typename...> class... From>
constexpr decltype(auto) are_convertible_to(std::string_view concept_name)
{
  return make_concept_item<details::are_convertible_to<To, From...>>(concept_name);
}

// Refines utility
template <typename... Ts, typename C>
constexpr decltype(auto) refines(const C& c)
{
  return c.template check<Ts...>();
}

template <auto... Vs, typename C>
constexpr decltype(auto) refines_v(const C& c)
{
  return c.template check_v<Vs...>();
}

}} // namespace blackmagic::concepts::utility
