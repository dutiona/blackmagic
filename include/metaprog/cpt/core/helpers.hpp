#pragma once

#ifndef METAPROG_CPT_CORE_HELPERS_HPP_
#define METAPROG_CPT_CORE_HELPERS_HPP_

#include "../../ctx/ctx.hpp"

#include <functional>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace cpt::helpers {

// nonesuch

struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};


// is_detected

namespace details {

template<typename...>
struct _parameters_pack {
};

template <typename Default, template<typename...> class Op, typename ParametersPack, typename = void>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <typename Default, template<typename...> class Op, template<typename...> class ParametersPack, typename... Args>
struct detector<Default, Op, ParametersPack<Args...>, std::void_t<Op<Args...>>> {
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <typename...> class Op, typename... Args>
using is_detected = typename details::detector<nonesuch, Op, details::_parameters_pack<Args...>>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = typename details::detector<nonesuch, Op, details::_parameters_pack<Args...>>::type;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = details::detector<Default, Op, details::_parameters_pack<Args...>>;

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


// invoke_result

namespace details {

template <typename AlwaysVoid, typename, typename...>
struct invoke_result {
};
template <typename F, typename... Args>
struct invoke_result<decltype(void(std::invoke(std::declval<F>(), std::declval<Args>()...))), F, Args...> {
  using type = decltype(std::invoke(std::declval<F>(), std::declval<Args>()...));
};

} // namespace details

template <typename F, typename... Args>
struct invoke_result : details::invoke_result<void, F, Args...> {
};
template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;


// dependent false
template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool()
  {
    return value;
  }
};
template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});


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
using make_trait_from_constructs = details::make_trait_from_constructs_impl<details::_parameters_pack<Constraints...>>;

template <typename... Predicates>
using make_trait_from_predicates = details::make_trait_from_predicates_impl<details::_parameters_pack<Predicates...>>;

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
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
};

template <bool SilentFailure, template <typename...> class Constraint, template <typename...> class ParametersPack,
          typename... Parameters>
struct make_concept_from_construct_impl<SilentFailure, Constraint, ParametersPack<Parameters...>,
                                        std::void_t<Constraint<Parameters...>>> : std::true_type {
};

template <bool SilentFailure, template <typename...> class Predicate, typename ParametersPack, typename = void>
struct make_concept_from_predicate_impl : std::false_type {
  static_assert(SilentFailure, "Concept checking failed. Use diagnostic to have more detailed about the failure.");
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
  using type =
    details::make_concept_from_construct_impl<SilentFailure, Constraint, details::_parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};

template <template <typename...> class Predicate>
struct make_concept_from_predicate {
  template <bool SilentFailure, typename... Parameters>
  using type =
    details::make_concept_from_predicate_impl<SilentFailure, Predicate, details::_parameters_pack<Parameters...>>;
  template <bool SilentFailure, typename... Parameters>
  using underlying_type = typename type<SilentFailure, Parameters...>::type;
  template <bool SilentFailure, typename... Parameters>
  static constexpr bool value = type<SilentFailure, Parameters...>::value;
};


// all_of / any_of constexpr
// TODO/FIXME remove this once fold expression are implemented
template <typename T>
constexpr bool all_of(T b)
{
  return b;
}
template <typename T, typename... Ts>
constexpr bool all_of(T b, Ts... bools)
{
  return b && all_of(bools...);
}

template <typename T>
constexpr bool any_of(T b)
{
  return b;
}
template <typename T, typename... Ts>
constexpr bool any_of(T b, Ts... bools)
{
  return b || any_of(bools...);
}

template <typename T>
constexpr size_t count(T b)
{
  return b;
}
template <typename T, typename... Ts>
constexpr size_t count(T b, Ts... bools)
{
  return b + count(bools...);
}

namespace details {

template <typename... Ts, size_t... I>
constexpr bool all_of_tuple(std::tuple<Ts...> tpl, std::index_sequence<I...>)
{
  return all_of(std::get<I>(tpl)...);
}

template <typename... Ts, size_t... I>
constexpr bool any_of_tuple(std::tuple<Ts...> tpl, std::index_sequence<I...>)
{
  return any_of(std::get<I>(tpl)...);
}

template <typename... Ts, size_t... I>
constexpr bool count_tuple(std::tuple<Ts...> tpl, std::index_sequence<I...>)
{
  return count(std::get<I>(tpl)...);
}

} // namespace details

template <typename... Ts>
constexpr bool all_of_tuple(std::tuple<Ts...> tpl)
{
  return details::all_of_tuple(tpl, std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool any_of_tuple(std::tuple<Ts...> tpl)
{
  return details::any_of_tuple(tpl, std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool count_tuple(std::tuple<Ts...> tpl)
{
  return details::count_tuple(tpl, std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr size_t end(std::tuple<Ts...>)
{
  return sizeof...(Ts);
}

// for_each/transform/accumulate/count_if/find_if for tuples
namespace details {

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  (std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}
template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  (std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func,
                                        Args&&... args)
{
  return std::make_tuple(std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...)...);
}

template <typename T, typename F, typename... Args, typename... Ts, size_t... I>
constexpr T accumulate_impl(T&& init, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  ((init = std::forward<F>(func)(std::forward<T>(init), std::get<I>(tpl), std::forward<Args>(args)...)), ...);
  return init;
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr size_t count_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  size_t ret = 0;
  ((ret += std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...) ? 1 : 0), ...);
  return ret;
}

template <typename... Ts>
constexpr size_t find_index_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<>)
{
  return end(tpl);
}

template <typename... Ts, size_t I, size_t... J>
constexpr size_t find_index_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I, J...>)
{
  return std::get<I>(tpl) ? I : find_index_if_impl(tpl, std::index_sequence<J...>{});
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...> idx, F&& func, Args&&... args)
{
  return find_index_if_impl(transform(tpl, std::forward<F>(func), std::forward<Args>(args)...), idx);
}

} // namespace details

template <typename F, typename... Args, typename... Ts>
constexpr void for_each(std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}
template <typename F, typename... Args, typename... Ts>
constexpr void for_each(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) transform(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                 std::forward<Args>(args)...);
}

template <typename T, typename F, typename... Args, typename... Ts>
constexpr decltype(auto) accumulate(T&& init, std::tuple<Ts...> tpl, F&& func, Args&&... args)
{
  return details::accumulate_impl(std::forward<T>(init), tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                  std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) count_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::count_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) find_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::find_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                               std::forward<Args>(args)...);
}

} // namespace cpt::helpers

// operator==(string_view, string_view) is not constexpr yet in libstdc++
constexpr bool equals(std::string_view lhs, std::string_view rhs)
{
#ifdef __GLIBCXX__
  return ctx::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
#else
  return lhs == rhs;
#endif // __GLIBCXX__
}

#endif // METAPROG_CPT_CORE_HELPERS_HPP_
