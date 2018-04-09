#pragma once

#include "concept_checker.hpp"
#include "helpers.hpp"

#include <metaprog/common/common.hpp>

#include <string_view>
#include <utility>

namespace metaprog::concepts { inline namespace core {

namespace common_helpers = metaprog::common::helpers;

template <typename Concept>
struct concept_item : std::pair<std::string_view, concept_checker<Concept>> {
  constexpr concept_item(std::string_view concept_name, concept_checker<Concept> cpt_ckr)
    : std::pair<std::string_view, concept_checker<Concept>>{concept_name, cpt_ckr}
  {
  }

  constexpr bool is(std::string_view concept_name) const
  {
    return common_helpers::equals(this->first, concept_name);
  }

  template <typename... Args>
  constexpr void require() const
  {
    require_concept<Concept, Args...>();
  }

  template <typename... Args>
  constexpr bool check() const
  {
    return check_concept<Concept, Args...>();
  }
};

template <typename ConceptLhs, typename ConceptRhs>
bool operator==(concept_item<ConceptLhs> lhs, concept_item<ConceptRhs> rhs)
{
  return lhs.is(rhs.first) && std::is_same_v<ConceptLhs, ConceptRhs>;
}

template <typename Concept>
constexpr decltype(auto) make_concept_item(std::string_view concept_name)
{
  return concept_item<Concept>{concept_name, concept_checker<Concept>{}};
}

template <template <typename...> class Constraint>
constexpr decltype(auto) make_concept_item_from_construct(std::string_view concept_name)
{
  return make_concept_item<helpers::make_concept_from_construct<Constraint>>(concept_name);
}

template <template <typename...> class Predicate>
constexpr decltype(auto) make_concept_item_from_predicate(std::string_view concept_name)
{
  return make_concept_item<helpers::make_concept_from_predicate<Predicate>>(concept_name);
}

template <typename... Bs>
using make_predicate = std::conjunction<Bs...>;

template <bool B>
using make_condition = std::bool_constant<B>;

namespace details {

template <typename Expr, typename = void>
struct make_expressions : std::false_type {
};

template <template <typename...> class Holder, typename... Expr>
struct make_expressions<Holder<Expr...>, std::void_t<decltype(helpers::valid_expr_v(std::declval<Expr>()...))>>
  : std::true_type {
};

} // namespace details

template <typename... Expr>
using make_expressions = details::make_expressions<type::basic_list<Expr...>>;

}} // namespace metaprog::concepts::core
