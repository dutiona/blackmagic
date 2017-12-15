#pragma once

#ifndef METAPROG_CPT_VERIF_HPP_
#define METAPROG_CPT_VERIF_HPP_

#include <stdexcept>

namespace cpt {

// force fail at compile time when concept isn't verified
template <template <bool, typename...> typename Concept, typename... Args>
constexpr void require()
{
  const auto silent_failure = false; // force trace (i.e. static_assert) upon failure
  if constexpr (!Concept<silent_failure, Args...>::value) {
    // needed only for ill-implemented concept that don't static_assert upon failure
    throw std::logic_error("Concept assertion error.");
  }
}

// force non failure at compile time when concept isn't verified
template <template <bool, typename...> typename Concept, typename... Args>
constexpr bool check()
{
  const auto silent_failure = true; // force no trace (i.e. no static_assert) upon failure
  return Concept<silent_failure, Args...>::value;
}

} // namespace cpt

#endif // METAPROG_CPT_VERIF_HPP_
