#pragma once

#ifndef METAPROG_CPT_CORE_DETAILS_CONCEPT_CHECKER_HPP_
#define METAPROG_CPT_CORE_DETAILS_CONCEPT_CHECKER_HPP_

namespace cpt {

// Helper class storing a concept to perform a check later on
template <typename Concept>
struct concept_checker {
  constexpr concept_checker() = default;

  // force non failure at compile time when concept isn't verified
  template <typename... Args>
  constexpr bool check() const
  {
    const auto silent_failure = true; // force no trace (i.e. no static_assert) upon failure
    return Concept::template value<silent_failure, Args...>;
  }

  // force fail at compile time when concept isn't verified
  template <typename... Args>
  constexpr void require() const
  {
    const auto silent_failure = false; // force trace (i.e. static_assert) upon failure
    static_assert(Concept::template value<silent_failure, Args...>, "Concept assertion error");
  }
};

// Quick check/require a concept via helper function
template <typename Concept, typename... Args>
constexpr void require_concept()
{
  concept_checker<Concept>{}.template require<Args...>();
}

template <typename Concept, typename... Args>
constexpr bool check_concept()
{
  return concept_checker<Concept>{}.template check<Args...>();
}

} // namespace cpt


#endif // METAPROG_CPT_CORE_DETAILS_CONCEPT_CHECKER_HPP_
