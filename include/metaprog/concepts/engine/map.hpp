#pragma once

#include "item.hpp"

#include <metaprog/tuple/tuple.hpp>

#include <string_view>
#include <tuple>

namespace metaprog::concepts { inline namespace engine {

namespace tuple = metaprog::tuple;

namespace details {

template <typename... Concepts>
constexpr bool ensure_unique_keys(item<Concepts>... concept_items)
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
struct map : std::tuple<item<Concepts>...> {
  constexpr map(item<Concepts>... items)
    : std::tuple<item<Concepts>...>{items...}
  {
    if (!details::ensure_unique_keys(items...)) {
      throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    }
  }

  constexpr size_t count() const
  {
    return std::tuple_size_v<map<Concepts...>>;
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
constexpr decltype(auto) make_concept_map(item<Concepts>... items)
{
  return map<Concepts...>{items...};
}

// Merge maps functions
template <typename... ConceptLhs, typename... ConceptRhs>
constexpr decltype(auto) merge_maps(map<ConceptLhs...> map_lhs, map<ConceptRhs...> map_rhs)
{
  return map<ConceptLhs..., ConceptRhs...>{std::tuple_cat(map_lhs, map_rhs)};
}

template <typename ConceptMap>
constexpr decltype(auto) merge_all_maps(ConceptMap map)
{
  return map;
}

template <typename ConceptMap, typename... ConceptMaps>
constexpr decltype(auto) merge_all_maps(ConceptMap map, ConceptMaps... maps)
{
  return merge_maps(map, merge_all_maps(maps...));
}

}} // namespace metaprog::concepts::engine
