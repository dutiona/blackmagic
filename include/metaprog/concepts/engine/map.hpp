#pragma once

#include "diagnostic.hpp"
#include "item.hpp"

#include "../../tuple/tuple.hpp"

#include <string_view>
#include <tuple>

namespace metaprog::concepts { inline namespace engine {

namespace tuple = metaprog::tuple;

namespace details {

template <typename... Items>
constexpr bool ensure_unique_keys(Items&&... concept_items)
{
  const auto items = std::make_tuple(concept_items...);
  return tuple::accumulate(
           size_t(0), items,
           [items](int count, auto cpt) {
             return count + tuple::count_if(items, [cpt_name = cpt.first](auto cpt_) { return cpt_.is(cpt_name); });
           })
         == sizeof...(Items);
}

template <typename... Items, size_t... I>
constexpr bool ensure_unique_keys(std::tuple<Items...> tuple_items, std::index_sequence<I...>)
{
  return ensure_unique_keys(std::get<I>(tuple_items)...);
}

} // namespace details


template <typename... Items>
struct map {
  const std::tuple<Items...> items_;

  constexpr map(Items&&... items)
    : items_{std::forward<Items>(items)...}
  {
    // if (!details::ensure_unique_keys(items...)) {
    //  throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    //}
  }

  constexpr map(const std::tuple<Items...>& items)
    : items_{items}
  {
    // if (!details::ensure_unique_keys(items, std::index_sequence_for<Items...>{})) {
    //  throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    //}
  }


  constexpr size_t count() const
  {
    return std::tuple_size_v<decltype(items_)>;
  }

  constexpr size_t count_if(std::string_view concept_name) const
  {
    return tuple::count_if(items_, [concept_name](auto cpt) { return cpt.is(concept_name); });
  }

  constexpr bool has(std::string_view concept_name) const
  {
    return tuple::find_if(items_, [concept_name](auto cpt) { return cpt.is(concept_name); }) != tuple::end(items_);
  }

  template <typename... Args>
  constexpr void require() const
  {
    tuple::for_each(items_, [](auto cpt) { cpt.template require<Args...>(); });
  }

  template <typename... Args>
  constexpr void require_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    tuple::for_each(items_, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        cpt.template require<Args...>();
      }
    });
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return tuple::all_of(tuple::transform(items_, [](auto cpt) { return cpt.template check<Args...>(); }));
  }

  template <typename... Args>
  constexpr bool check_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    return tuple::all_of(tuple::transform(items_, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        return cpt.template check<Args...>();
      }
      return true;
    }));
  }

  template <typename This, typename... Args>
  using can_call_diagnose_t = decltype(metaprog::concepts::diagnostic::traits<This>::template diagnose<Args...>());

  template <typename... Args>
  constexpr void diagnostic() const
  {
    static_assert(common_helpers::is_detected_v<can_call_diagnose_t, std::decay_t<decltype(*this)>, Args...>,
                  "No diagnostic trait provided for this concept type.");

    metaprog::concepts::diagnostic::traits<std::decay_t<decltype(*this)>>::template diagnose<Args...>();
  }
};


namespace details {

template <typename... Items>
constexpr auto make_map(const std::tuple<Items...>& items)
{
  return map<Items...>{items};
}

template <typename... Items>
constexpr auto make_unique_map(const std::tuple<Items...>& items)
{
  // return make_map(tuple::unique(items));
  return make_map(items);
}

// Merge maps functions
template <typename... ItemsLhs, typename... ItemsRhs>
constexpr auto merge_maps(const map<ItemsLhs...>& map_lhs, const map<ItemsRhs...>& map_rhs)
{
  return details::make_unique_map(std::tuple_cat(map_lhs.items_, map_rhs.items_));
}

template <typename ConceptMap>
constexpr auto merge_all_maps(ConceptMap&& map)
{
  return std::forward<ConceptMap>(map);
}

template <typename ConceptMap, typename... ConceptMaps>
constexpr auto merge_all_maps(ConceptMap&& map, ConceptMaps&&... maps)
{
  return merge_maps(std::forward<ConceptMap>(map), merge_all_maps(std::forward<ConceptMaps>(maps)...));
}

template <typename... Items>
constexpr decltype(auto) make_concept_map(map<Items...> map)
{
  return map;
}

template <typename Concept>
constexpr decltype(auto) make_concept_map(item<Concept> it)
{
  return map<item<Concept>>{it};
}
} // namespace details

template <typename... ItemsOrMaps>
constexpr auto make_concept_map(ItemsOrMaps&&... items_or_maps)
{
  return details::merge_all_maps(details::make_concept_map(std::forward<ItemsOrMaps>(items_or_maps))...);
}

}} // namespace metaprog::concepts::engine
