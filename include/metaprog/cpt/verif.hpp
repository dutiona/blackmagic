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
      throw std::logic_error("Concept assertion error");
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
// using concept_item_t = ctx::pair<ctx::string, concept_checker<Concept>>;
using concept_item_t = ctx::pair<int, concept_checker<Concept>>;

template <typename Concept>
constexpr decltype(auto) make_concept_item(int /*ctx::string*/ s)
{
  return ctx::make_pair(s, concept_checker<Concept>{});
};

template <typename... Concepts>
using concept_map_t = std::tuple<concept_item_t<Concepts>...>;

template <typename... Concepts>
constexpr decltype(auto) make_concept_map(concept_item_t<Concepts>... concept_items)
{
  return std::make_tuple(concept_items...);
}

namespace details {

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
constexpr void require_map_at_impl(concept_map_t<Concepts...> concept_map, int /*ctx::string*/ index,
                                   std::index_sequence<I...>)
{
  const auto require_if = [index](auto cpt) {
    if (cpt.first == index) {
      cpt.second.template require<Args...>();
    }
  };
  (require_if(std::get<I>(concept_map)), ...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_impl(concept_map_t<Concepts...> concept_map, std::index_sequence<I...>)
{
  return all_of(std::get<I>(concept_map).second.template check<Args...>()...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_at_impl([[maybe_unused]] concept_map_t<Concepts...> concept_map,
                                 [[maybe_unused]] int /*ctx::string*/        index, std::index_sequence<I...>)
{
  const auto check_if = [index](auto cpt) {
    if (cpt.first == index) {
      return cpt.second.template check<Args...>();
    }
    return true;
  };
  return all_of(check_if(std::get<I>(concept_map))...);
}

} // namespace details

// require map functions
template <typename... Args, typename... Concepts>
constexpr void require_map(concept_map_t<Concepts...> concept_map)
{
  details::require_map_impl<Args...>(concept_map, std::make_index_sequence<sizeof...(Concepts)>{});
}

template <typename... Args, typename... Concepts>
constexpr void require_map_at(concept_map_t<Concepts...> concept_map, int /*ctx::string*/ index)
{
  details::require_map_at_impl<Args...>(concept_map, index, std::make_index_sequence<sizeof...(Concepts)>{});
}

// check map functions

template <typename... Args, typename... Concepts>
constexpr bool check_map(concept_map_t<Concepts...> concept_map)
{
  return details::check_map_impl<Args...>(concept_map, std::make_index_sequence<sizeof...(Concepts)>{});
}

template <typename... Args, typename... Concepts>
constexpr bool check_map_at(concept_map_t<Concepts...> concept_map, int /*ctx::string*/ index)
{
  return details::check_map_at_impl<Args...>(concept_map, index, std::make_index_sequence<sizeof...(Concepts)>{});
}

} // namespace cpt

#endif // METAPROG_CPT_VERIF_HPP_
