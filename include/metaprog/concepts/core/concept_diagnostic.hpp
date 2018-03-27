#pragma once

#include <metaprog/common/common.hpp>

// Diagnostic helpers
namespace metaprog::diagnostic {

namespace helpers = metaprog::common::helpers;

template <typename... Args, typename ConceptMap>
constexpr void diagnostic(ConceptMap)
{
  static_assert(helpers::dependent_false_v<ConceptMap, Args...>,
                "No diagnostic function helpers made for this concept");
}

} // namespace metaprog::diagnostic

// Here we cannot make a helpers function template because of the two phase name lookup.
// Even if a more specialized diagnostic overload exists, it won't be selected at ADL
// So we have to make a macro
#define DIAGNOSTIC(concept_map, ...) metaprog::diagnostic::diagnostic<__VA_ARGS__>(concept_map)
