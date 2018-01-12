#pragma once

#ifndef METAPROG_CPT_CORE_CONCEPT_DIAGNOSTIC_HPP_
#define METAPROG_CPT_CORE_CONCEPT_DIAGNOSTIC_HPP_

#include "helpers.hpp"


// Diagnostic helpers
namespace concept_diagnostic_traits {
template <typename... Args, typename ConceptMap>
constexpr void diagnostic(ConceptMap)
{
  static_assert(cpt::helpers::dependent_false_v<ConceptMap, Args...>,
                "No diagnostic function helpers made for this concept");
}

} // namespace concept_diagnostic_traits

// Here we cannot make a helpers function template because of the two phase name lookup.
// Even if a more specialized diagnostic overload exists, it won't be selected at ADL
// So we have to make a macro
#define DIAGNOSTIC(concept_map, ...) concept_diagnostic_traits::diagnostic<__VA_ARGS__>(concept_map)


#endif // METAPROG_CPT_CORE_CONCEPT_DIAGNOSTIC_HPP_
