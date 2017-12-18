#pragma once

#ifndef METAPROG_CPT_VERIF_HPP_
#define METAPROG_CPT_VERIF_HPP_

#include "../ctx/ctx.hpp"
#include "cpt.hpp"

#include <iostream>
#include <stdexcept>
#include <tuple>
#include <typeinfo>
#include <utility>

namespace cpt {

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
      throw std::logic_error("Concept assertion error.");
    }
  }
};

// Quick require via helper function
template <typename Concept, typename... Args>
constexpr void require()
{
  concept_checker<Concept>{}.template require<Args...>();
}

// Quick check via helper function
template <typename Concept, typename... Args>
constexpr bool check()
{
  return concept_checker<Concept>{}.template check<Args...>();
}


template <typename Concept>
using concept_item_t = ctx::pair<ctx::string, concept_checker<Concept>>;

template <typename Concept>
constexpr decltype(auto) make_concept_item(ctx::string s)
{
  return concept_item_t<Concept>{s, Concept{}};
}

/*
template <typename... Concepts>
using concept_map_t = std::tuple<concept_item_t<Concepts>...>;

template <typename... Concepts>
constexpr decltype(auto) make_concept_map(concept_item_t<Concepts>... concept_items)
{
  return std::make_tuple(concept_items...);
}

template <typename... Concepts, size_t... I>
constexpr void require_map_impl(concept_map_t<Concepts...> concept_map, std::index_sequence<I...>)
{
  ((std::cout << typeid(require<std::get<I>(concept_map).second>()).name()), ...) << std::endl;
  //(std::get<I>(concept_map), ...);
}

template <typename... Concepts>
constexpr void require_map(concept_map_t<Concepts...> concept_map)
{
  require_map_impl(concept_map, std::make_index_sequence<sizeof...(Concepts)>{});
}
*/

} // namespace cpt

#endif // METAPROG_CPT_VERIF_HPP_
