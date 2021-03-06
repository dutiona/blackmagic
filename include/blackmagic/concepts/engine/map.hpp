#pragma once

#include "diagnostic.hpp"
#include "item.hpp"

#include "../../common/detector.hpp"
#include "../../tuple/algorithm/accumulate.hpp"
#include "../../tuple/algorithm/all.hpp"
#include "../../tuple/algorithm/count_if.hpp"
#include "../../tuple/algorithm/find_if.hpp"
#include "../../tuple/algorithm/for_each.hpp"
#include "../../tuple/algorithm/transform.hpp"
#include "../../tuple/algorithm/unique.hpp"
#include "../../tuple/algorithm/unpack.hpp"

#include <string_view>
#include <tuple>

namespace blackmagic::concepts { inline namespace engine {

namespace details {

struct ensure_unique_keys_t {
  template <typename... Items>
  constexpr bool operator()(Items&&... concept_items) const
  {
    const auto items = std::make_tuple(concept_items...);
    return tuple::accumulate(
             size_t(0), items,
             [items](int count, auto cpt) {
               return count + tuple::count_if(items, [cpt_name = cpt.first](auto cpt_) { return cpt_.is(cpt_name); });
             })
           == sizeof...(Items);
  }
};

inline constexpr ensure_unique_keys_t ensure_unique_keys{};

} // namespace details


template <typename... Items>
struct map {
  const std::tuple<Items...> items_;

  constexpr map(Items&&... items)
    : items_{std::forward<Items>(items)...}
  {
    if (!details::ensure_unique_keys(std::forward<Items>(items)...)) {
      throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    }
  }

  constexpr map(const std::tuple<Items...>& items)
    : items_{items}
  {
    if (!tuple::unpack(items, details::ensure_unique_keys)) {
      throw "Duplicate keys (concept name) in the concept map : the same concept is here twice ?";
    }
  }


  constexpr size_t count() const
  {
    return std::tuple_size_v<std::remove_reference_t<decltype(items_)>>;
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

  template <auto... Args>
  constexpr void require_v() const
  {
    tuple::for_each(items_, [](auto cpt) { cpt.template require_v<Args...>(); });
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

  template <auto... Args>
  constexpr void require_v_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    tuple::for_each(items_, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        cpt.template require_v<Args...>();
      }
    });
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return tuple::all(tuple::transform(items_, [](auto cpt) { return cpt.template check<Args...>(); }));
  }

  template <auto... Args>
  constexpr bool check_v() const
  {
    return tuple::all(tuple::transform(items_, [](auto cpt) { return cpt.template check_v<Args...>(); }));
  }

  template <typename... Args>
  constexpr bool check_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    return tuple::all(tuple::transform(items_, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        return cpt.template check<Args...>();
      }
      return true;
    }));
  }

  template <auto... Args>
  constexpr bool check_v_at(std::string_view concept_name) const
  {
    if (!has(concept_name)) {
      throw "This concept key doesn't exists in this concept map!";
    }

    return tuple::all(tuple::transform(items_, [concept_name](auto cpt) {
      if (cpt.is(concept_name)) {
        return cpt.template check_v<Args...>();
      }
      return true;
    }));
  }

  template <typename This, typename... Args>
  using can_call_diagnose_t = decltype(diagnostic::traits<This>::template diagnose<Args...>());

  template <typename... Args>
  constexpr void diagnostic() const
  {
    static_assert(common::is_detected_v<can_call_diagnose_t, std::decay_t<decltype(*this)>, Args...>,
                  "No diagnostic trait provided for this concept type.");

    diagnostic::traits<std::decay_t<decltype(*this)>>::template diagnose<Args...>();
  }

  template <typename This, auto... Args>
  using can_call_diagnose_v_t = decltype(diagnostic::traits<This>::template diagnose_v<Args...>());

  template <auto... Args>
  constexpr void diagnostic_v() const
  {
    static_assert(common::is_detected_v<can_call_diagnose_v_t, std::decay_t<decltype(*this)>, Args...>,
                  "No diagnostic trait provided for this concept type.");

    diagnostic::traits<std::decay_t<decltype(*this)>>::template diagnose_v<Args...>();
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
  return make_map(tuple::unique(items));
  // return make_map(items);
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

}} // namespace blackmagic::concepts::engine
