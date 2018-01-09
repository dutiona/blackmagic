#pragma once

#ifndef METAPROG_CPT_VERIF_HPP_
#define METAPROG_CPT_VERIF_HPP_

#include "helpers.hpp"
#include "verif.hpp"

#include "../ctx/ctx.hpp"

#include <stdexcept>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

namespace cpt {
namespace details {
// Helper class storing a concept to perform a check later on
template <typename Concept>
struct concept_checker {
  constexpr concept_checker() = default;

  // force non failure at compile time when concept isn't verified
  template <typename... Args>
  constexpr bool check()
  {
    const auto silent_failure = true; // force no trace (i.e. no static_assert) upon failure
    return Concept::template value<silent_failure, Args...>;
  }

  // force fail at compile time when concept isn't verified
  template <typename... Args>
  constexpr void require()
  {
    const auto silent_failure = false; // force trace (i.e. static_assert) upon failure
    if constexpr (!Concept::template value<silent_failure, Args...>) {
      // needed only for ill-implemented concept that don't static_assert upon failure
      throw std::logic_error("Concept assertion error");
    }
  }
};
} // namespace details

template <typename Concept>
using concept_item_t = std::pair<std::string_view, details::concept_checker<Concept>>;

template <typename... Concepts>
using concept_map_t = std::tuple<concept_item_t<Concepts>...>;

namespace details {
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

template <typename... Args, typename... Concepts, size_t... I>
constexpr void require_map_impl(concept_map_t<Concepts...> concept_map, std::index_sequence<I...>)
{
  (std::get<I>(concept_map).second.template require<Args...>(), ...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr void require_map_at_impl(concept_map_t<Concepts...> concept_map, std::string_view concept_name,
                                   std::index_sequence<I...>)
{
  const auto require_if = [](auto cpt, std::string_view concept_name) {
    if (ctx::equal(cpt.first.cbegin(), cpt.first.cend(), concept_name.cbegin(), concept_name.cend())) {
      cpt.second.template require<Args...>();
    }
  };
  (require_if(std::get<I>(concept_map), concept_name), ...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_impl(concept_map_t<Concepts...> concept_map, std::index_sequence<I...>)
{
  return all_of(std::get<I>(concept_map).second.template check<Args...>()...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_at_impl(concept_map_t<Concepts...> concept_map, std::string_view concept_name,
                                 std::index_sequence<I...>)
{
  const auto check_if = [](auto cpt, std::string_view concept_name) {
    if (ctx::equal(cpt.first.cbegin(), cpt.first.cend(), concept_name.cbegin(), concept_name.cend())) {
      return cpt.second.template check<Args...>();
    }
    return true;
  };
  return all_of(check_if(std::get<I>(concept_map), concept_name)...);
}

} // namespace details

// TODO/FIXME deprecate those 2 functions and put them in details
// Quick check/require a concept via helper function
template <typename Concept, typename... Args>
constexpr void require()
{
  details::concept_checker<Concept>{}.template require<Args...>();
}

template <typename Concept, typename... Args>
constexpr bool check()
{
  return details::concept_checker<Concept>{}.template check<Args...>();
}

// Quick check/require an item via helper function
template <typename... Args, typename Concept>
constexpr void require(concept_item_t<Concept>)
{
  require<Concept, Args...>();
}

template <typename... Args, typename Concept>
constexpr bool check(concept_item_t<Concept>)
{
  return check<Concept, Args...>();
}

// helpers functions
template <typename Concept>
constexpr decltype(auto) make_concept_item(std::string_view concept_name)
{
  return std::make_pair(concept_name, details::concept_checker<Concept>{});
}

template <typename... Concepts>
constexpr decltype(auto) make_concept_map(concept_item_t<Concepts>... concept_items)
{
  return std::make_tuple(concept_items...);
}

// require map functions
template <typename... Args, typename... Concepts>
constexpr void require_map(concept_map_t<Concepts...> concept_map)
{
  details::require_map_impl<Args...>(concept_map, std::make_index_sequence<sizeof...(Concepts)>{});
}

template <typename... Args, typename... Concepts>
constexpr void require_map_at(concept_map_t<Concepts...> concept_map, std::string_view concept_name)
{
  details::require_map_at_impl<Args...>(concept_map, concept_name, std::make_index_sequence<sizeof...(Concepts)>{});
}

// check map functions
template <typename... Args, typename... Concepts>
constexpr bool check_map(concept_map_t<Concepts...> concept_map)
{
  return details::check_map_impl<Args...>(concept_map, std::make_index_sequence<sizeof...(Concepts)>{});
}

// TODO/FIXME this doesn't work... The result cannot be stored/used in a constexpr context...
template <typename... Args, typename... Concepts>
constexpr bool check_map_at(concept_map_t<Concepts...> concept_map, std::string_view concept_name)
{
  return details::check_map_at_impl<Args...>(concept_map, concept_name,
                                             std::make_index_sequence<sizeof...(Concepts)>{});
}

// Merge maps functions
template <typename... ConceptLhs, typename... ConceptRhs>
constexpr auto merge_maps(concept_map_t<ConceptLhs...> map_lhs, concept_map_t<ConceptRhs...> map_rhs)
{
  return std::tuple_cat(map_lhs, map_rhs);
}

template <typename ConceptMap>
constexpr auto merge_all_maps(ConceptMap concept_map)
{
  return concept_map;
}

template <typename ConceptMap, typename... ConceptMaps>
constexpr auto merge_all_maps(ConceptMap map, ConceptMaps... concept_maps)
{
  return merge_maps(map, merge_all_maps(concept_maps...));
}

// helpers for building concepts
template <template <typename...> class Constraint>
constexpr auto make_concept_item_from_construct(std::string_view concept_name)
{
  return cpt::make_concept_item<cpt::make_concept_from_construct<Constraint>>(concept_name);
}

template <template <typename...> class Predicate>
constexpr auto make_concept_item_from_predicate(std::string_view concept_name)
{
  return cpt::make_concept_item<cpt::make_concept_from_predicate<Predicate>>(concept_name);
}

} // namespace cpt

// Diagnostic helpers
namespace concept_diagnostic_traits {
template <typename... Args, typename ConceptMap>
constexpr void diagnostic(ConceptMap)
{
  static_assert(cpt::helpers::dependent_false_v<ConceptMap, Args...>,
                "No diagnostic function helpers made for this concept");
}

} // namespace concept_diagnostic_traits

// Here we cannot make a helpers function template because of the two phase name lookup.
// Even if a more specialized diagnostic overload exists, it won't be selected at ADL
// So we have to make a macro
#define DIAGNOSTIC(concept_map, ...) concept_diagnostic_traits::diagnostic<__VA_ARGS__>(concept_map)


#endif // METAPROG_CPT_VERIF_HPP_
