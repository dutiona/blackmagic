#pragma once

#include "checker.hpp"

#include <string_view>
#include <utility>

namespace blackmagic::concepts { inline namespace engine {

template <typename Concept>
struct item : std::pair<std::string_view, checker<Concept>> {
  constexpr item(std::string_view concept_name, checker<Concept> cpt_ckr)
    : std::pair<std::string_view, checker<Concept>>{concept_name, cpt_ckr}
  {
  }

  constexpr bool is(std::string_view concept_name) const
  {
    return this->first == concept_name;
  }

  template <typename... Args>
  constexpr void require() const
  {
    require_concept<Concept, Args...>();
  }

  template <auto... Args>
  constexpr void require_v() const
  {
    require_v_concept<Concept, Args...>();
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return check_concept<Concept, Args...>();
  }

  template <auto... Args>
  constexpr bool check_v() const
  {
    return check_v_concept<Concept, Args...>();
  }
};

template <typename ConceptLhs, typename ConceptRhs>
bool operator==(item<ConceptLhs> lhs, item<ConceptRhs> rhs)
{
  return lhs.is(rhs.first) && std::is_same_v<ConceptLhs, ConceptRhs>;
}

template <typename Concept>
constexpr decltype(auto) make_concept_item(std::string_view concept_name)
{
  return item<Concept>{concept_name, checker<Concept>{}};
}

}} // namespace blackmagic::concepts::engine
