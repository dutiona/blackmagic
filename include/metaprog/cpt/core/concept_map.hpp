#pragma once

#ifndef METAPROG_CPT_CORE_CONCEPT_MAP_HPP_
#define METAPROG_CPT_CORE_CONCEPT_MAP_HPP_

#include "concept_item.hpp"
#include "helpers.hpp"

#include <string_view>
#include <tuple>

namespace cpt {

template <typename... Concepts>
struct concept_map;

namespace details {

template <typename... Concepts>
constexpr bool ensure_unique_keys(concept_item<Concepts>... concept_items)
{
  auto items = std::make_tuple(std::forward<concept_item<Concepts>>(concept_items)...);
  return helpers::accumulate(
           static_cast<size_t>(0), items,
           [](int count, auto cpt, auto cpt_map) {
             return count
                    + helpers::count_if(cpt_map, [](auto cpt_, std::string_view cn) { return cpt_.is(cn); }, cpt.first);
           },
           items)
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
    return helpers::count_if(*this, [](auto cpt, std::string_view cn) { return cpt.is(cn); }, concept_name);
  }

  constexpr bool has(std::string_view concept_name) const
  {
    return helpers::find_if(*this, [](auto cpt, std::string_view cn) { return cpt.is(cn); }, concept_name)
           != end(*this);
  }

  template <typename... Args>
  constexpr void require() const
  {
    helpers::for_each(*this, [](auto cpt) { cpt.second.template require<Args...>(); });
  }

  template <typename... Args>
  constexpr void require_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    helpers::for_each(*this,
                      [](auto cpt, std::string_view cn) {
                        if (cpt.first == cn) {
                          cpt.second.template require<Args...>();
                        }
                      },
                      concept_name);
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return helpers::all_of_tuple(
      helpers::transform(*this, [](auto cpt) { return cpt.second.template check<Args...>(); }));
  }

  template <typename... Args>
  constexpr bool check_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    return helpers::all_of_tuple(helpers::transform(*this,
                                                    [](auto cpt, std::string_view cn) {
                                                      if (cpt.first == cn) {
                                                        return cpt.second.template check<Args...>();
                                                      }
                                                      return true;
                                                    },
                                                    concept_name));
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
