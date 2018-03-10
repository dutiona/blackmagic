#pragma once

#ifndef METAPROG_CPT_CORE_CONCEPT_MAP_HPP_
#define METAPROG_CPT_CORE_CONCEPT_MAP_HPP_

#include "../../tuple/tuple.hpp"
#include "concept_item.hpp"

#include <string_view>
#include <tuple>

namespace cpt {

namespace details {

template <typename... Concepts>
constexpr bool ensure_unique_keys(concept_item<Concepts>... concept_items)
{
  const auto items = std::make_tuple(concept_items...);
  return tuple::accumulate(
           size_t(0), items,
           [items](int count, auto cpt) {
             return count + tuple::count_if(items, [cpt_name = cpt.first](auto cpt_) { return cpt_.is(cpt_name); });
           })
         == sizeof...(Concepts);
}

} // namespace details


template <typename... Concepts>
struct concept_map : std::tuple<concept_item<Concepts>...> {
  constexpr concept_map(concept_item<Concepts>... concept_items)
    : std::tuple<concept_item<Concepts>...>{concept_items...}
  {
    if (!details::ensure_unique_keys(concept_items...)) {
      throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    }
  }

  constexpr size_t count() const
  {
    return std::tuple_size_v<concept_map<Concepts...>>;
  }

  constexpr size_t count_if(std::string_view concept_name) const
  {
    return tuple::count_if(*this, [concept_name](auto cpt) { return cpt.is(concept_name); });
  }

  constexpr bool has(std::string_view concept_name) const
  {
    return tuple::find_if(*this, [concept_name](auto cpt) { return cpt.is(concept_name); }) != tuple::end(*this);
  }

  template <typename... Args>
  constexpr void require() const
  {
    tuple::for_each(*this, [](auto cpt) { cpt.template require<Args...>(); });
  }

  template <typename... Args>
  constexpr void require_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    tuple::for_each(*this, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        cpt.template require<Args...>();
      }
    });
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return tuple::all_of(tuple::transform(*this, [](auto cpt) { return cpt.template check<Args...>(); }));
  }

  template <typename... Args>
  constexpr bool check_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    return tuple::all_of(tuple::transform(*this, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        return cpt.template check<Args...>();
      }
      return true;
    }));
  }
};

template <typename... Concepts>
constexpr decltype(auto) make_concept_map(concept_item<Concepts>... concept_items)
{
  return concept_map<Concepts...>{concept_items...};
}

// Merge maps functions
template <typename... ConceptLhs, typename... ConceptRhs>
constexpr decltype(auto) merge_maps(concept_map<ConceptLhs...> map_lhs, concept_map<ConceptRhs...> map_rhs)
{
  return concept_map<ConceptLhs..., ConceptRhs...>{std::tuple_cat(map_lhs, map_rhs)};
}

template <typename ConceptMap>
constexpr decltype(auto) merge_all_maps(ConceptMap concept_map)
{
  return concept_map;
}

template <typename ConceptMap, typename... ConceptMaps>
constexpr decltype(auto) merge_all_maps(ConceptMap map, ConceptMaps... concept_maps)
{
  return merge_maps(map, merge_all_maps(concept_maps...));
}

} // namespace cpt


#endif // METAPROG_CPT_CORE_CONCEPT_MAP_HPP_
