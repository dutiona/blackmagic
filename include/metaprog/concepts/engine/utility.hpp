#pragma once

#include <metaprog/type/type.hpp>

#include <type_traits>

namespace metaprog::concepts { inline namespace utility {

namespace type = metaprog::type;

struct valid_expr_t {
  template <typename... T>
  void operator()(T&&...) const;
};
inline constexpr auto valid_expr_v = valid_expr_t{};

struct same_type_t {
  template <typename T, typename U>
  auto operator()(T&&, U&&) const -> type::call_t<type::if_<std::is_same_v<T, U>>, int>;
};
inline constexpr auto same_type_v = same_type_t{};

struct is_true_t {
  template <typename Bool>
  auto operator()(Bool) const -> type::call_t<type::if_<Bool::value>, int>;
};
inline constexpr auto is_true_v = is_true_t{};

struct is_false_t {
  template <typename Bool>
  auto operator()(Bool) const -> type::call_t<type::if_<!Bool::value>, int>;
};
inline constexpr auto is_false_v = is_false_t{};

namespace details {

template <typename Ret, typename T>
Ret returns_(T const&);
}

template <typename T, typename U>
auto convertible_to(U&& u) -> decltype(details::returns_<int>(static_cast<T>((U &&) u)));


// traits helper

namespace details {

template <typename Holder, typename = void>
struct make_trait_from_constructs_impl : std::false_type {
};
template <template <typename... Constraints> class Holder, typename... Constraints>
struct make_trait_from_constructs_impl<Holder<Constraints...>, std::void_t<Constraints...>> : std::true_type {
};

template <typename Holder, typename = void>
struct make_trait_from_predicates_impl : std::false_type {
};
template <template <typename... Predicates> class Holder, typename... Predicates>
struct make_trait_from_predicates_impl<Holder<Predicates...>, std::enable_if_t<std::conjunction_v<Predicates...>>>
  : std::true_type {
};

} // namespace details

template <typename... Constraints>
using make_trait_from_constructs = details::make_trait_from_constructs_impl<type::list<Constraints...>>;

template <typename... Predicates>
using make_trait_from_predicates = details::make_trait_from_predicates_impl<type::list<Predicates...>>;

// TODO/FIXME investigate this issue.
// We can't use :
// template <typename T>
// struct is_mytrait : helpers::make_trait_from_constructs<decltype(...<T>...)> {};
// yet because it's not a SFINAE context... :(
// Maybe in a fully fledge c++17/20 compiler with the extension of SFINAE context...
// Or maybe it's a compiler bug.


// concept helpers
namespace details {

template <bool SilentFailure, template <typename...> class Constraint, typename ParametersPack, typename = void>
struct make_concept_from_construct_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed.");
};

template <bool SilentFailure, template <typename...> class Constraint, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_concept_from_construct_impl<SilentFailure, Constraint, ParametersPack<Parameters...>,
                                        std::void_t<Constraint<Parameters...>>> : std::true_type {
};

template <bool SilentFailure, template <typename...> class Predicate, typename ParametersPack, typename = void>
struct make_concept_from_predicate_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed.");
};

template <bool SilentFailure, template <typename...> class Predicate, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_concept_from_predicate_impl<SilentFailure, Predicate, ParametersPack<Parameters...>,
                                        std::enable_if_t<Predicate<Parameters...>::value>> : std::true_type {
};

} // namespace details

template <template <typename...> class Constraint>
struct make_concept_from_construct {
  template <bool SilentFailure, typename... Parameters>
  using type = details::make_concept_from_construct_impl<SilentFailure, Constraint, type::basic_list<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <template <typename...> class Predicate>
struct make_concept_from_predicate {
  template <bool SilentFailure, typename... Parameters>
  using type = details::make_concept_from_predicate_impl<SilentFailure, Predicate, type::basic_list<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <template <typename...> class Constraint>
constexpr decltype(auto) make_concept_item_from_construct(std::string_view concept_name)
{
  return make_concept_item<make_concept_from_construct<Constraint>>(concept_name);
}

template <template <typename...> class Predicate>
constexpr decltype(auto) make_concept_item_from_predicate(std::string_view concept_name)
{
  return make_concept_item<make_concept_from_predicate<Predicate>>(concept_name);
}

template <typename... Bs>
using make_predicate = std::conjunction<Bs...>;

template <bool B>
using make_condition = std::bool_constant<B>;

namespace details {

template <typename Expr, typename = void>
struct make_expressions : std::false_type {
};

template <template <typename...> class Holder, typename... Expr>
struct make_expressions<Holder<Expr...>, std::void_t<decltype(valid_expr_v(std::declval<Expr>()...))>>
  : std::true_type {
};

} // namespace details

template <typename... Expr>
using make_expressions = details::make_expressions<type::basic_list<Expr...>>;

}} // namespace metaprog::concepts::utility
