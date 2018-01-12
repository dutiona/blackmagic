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

template <typename... Concepts, size_t... I>
constexpr bool map_has_impl(concept_map<Concepts...> concept_map, std::string_view concept_name,
                            std::index_sequence<I...>)
{
  constexpr auto has_item = [](auto cpt, std::string_view cn) { return cpt.is(cn); };
  return helpers::any_of(has_item(std::get<I>(concept_map), concept_name)...);
}

template <typename... Concepts, size_t... I>
constexpr bool map_count_if_impl(concept_map<Concepts...> concept_map, std::string_view concept_name,
                                 std::index_sequence<I...>)
{
  constexpr auto has_item = [](auto cpt, std::string_view cn) { return cpt.is(cn); };
  return count(has_item(std::get<I>(concept_map), concept_name)...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr void require_map_impl(concept_map<Concepts...> concept_map, std::index_sequence<I...>)
{
  (std::get<I>(concept_map).second.template require<Args...>(), ...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr void require_map_at_impl(concept_map<Concepts...> concept_map, std::string_view concept_name,
                                   std::index_sequence<I...>)
{
  if (!concept_map.has(concept_name)) {
    throw "This concept key doesn't exists in this concept map!";
  }

  constexpr auto require_if = [](auto cpt, std::string_view concept_name) {
    if (ctx::equal(cpt.first.cbegin(), cpt.first.cend(), concept_name.cbegin(), concept_name.cend())) {
      cpt.second.template require<Args...>();
    }
  };

  (require_if(std::get<I>(concept_map), concept_name), ...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_impl(concept_map<Concepts...> concept_map, std::index_sequence<I...>)
{
  return helpers::all_of(std::get<I>(concept_map).second.template check<Args...>()...);
}

template <typename... Args, typename... Concepts, size_t... I>
constexpr bool check_map_at_impl(concept_map<Concepts...> concept_map, std::string_view concept_name,
                                 std::index_sequence<I...>)
{
  if (!concept_map.has(concept_name)) {
    throw "This concept key doesn't exists in this concept map!";
  }

  constexpr auto check_if = [](auto cpt, std::string_view cn) -> bool {
    if (ctx::equal(cpt.first.cbegin(), cpt.first.cend(), cn.cbegin(), cn.cend())) {
      return cpt.second.template check<Args...>();
    }
    return true;
  };

  return helpers::all_of(check_if(std::get<I>(concept_map), concept_name)...);
}

template <typename... Concepts, size_t... I>
constexpr bool ensure_unique_keys_impl(std::index_sequence<I...>, std::tuple<concept_item<Concepts>...> concept_items)
{
  auto keys = ctx::vector<std::string_view, sizeof...(Concepts)>{};

  (keys.push_back(std::get<I>(concept_items).first), ...);

  constexpr auto count_if = [](auto first, auto last, auto key) {
    size_t ret = 0;
    for (; first != last; ++first) {
      if (ctx::equal(first->cbegin(), first->cend(), key.cbegin(), key.cend())) {
        ret++;
      }
    }
    return ret;
  };

  size_t count_elems = 0;
  ((count_elems += count_if(keys.cbegin(), keys.cend(), std::get<I>(concept_items).first)), ...);

  return count_elems == keys.size();
}
template <typename... Concepts>
constexpr bool ensure_unique_keys(concept_item<Concepts>... concept_items)
{
  return ensure_unique_keys_impl(std::make_index_sequence<sizeof...(Concepts)>{},
                                 std::make_tuple(std::forward<concept_item<Concepts>>(concept_items)...));
}

} // namespace details


template <typename... Concepts>
struct concept_map : std::tuple<concept_item<Concepts>...> {
  constexpr concept_map(concept_item<Concepts>... concept_items)
    : std::tuple<concept_item<Concepts>...>{concept_items...}
  {
    if (!details::ensure_unique_keys(concept_items...)) {
      throw "Duplicate keys (concept name) in the concept map : the same concept is here twice !";
    }
  }

  constexpr size_t count() const
  {
    return std::tuple_size_v<concept_map<Concepts...>>;
  }

  constexpr size_t count_if(std::string_view concept_name) const
  {
    return details::map_count_if_impl(*this, concept_name, std::make_index_sequence<sizeof...(Concepts)>{});
  }

  constexpr bool has(std::string_view concept_name) const
  {
    return details::map_has_impl(*this, concept_name, std::make_index_sequence<sizeof...(Concepts)>{});
  }

  template <typename... Args>
  constexpr void require() const
  {
    details::require_map_impl<Args...>(*this, std::make_index_sequence<sizeof...(Concepts)>{});
  }

  template <typename... Args>
  constexpr void require_at(std::string_view concept_name) const
  {
    details::require_map_at_impl<Args...>(*this, concept_name, std::make_index_sequence<sizeof...(Concepts)>{});
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return details::check_map_impl<Args...>(*this, std::make_index_sequence<sizeof...(Concepts)>{});
  }

  template <typename... Args>
  constexpr bool check_at(std::string_view concept_name) const
  {
    return details::check_map_at_impl<Args...>(*this, concept_name, std::make_index_sequence<sizeof...(Concepts)>{});
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
