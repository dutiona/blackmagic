#pragma once

#ifndef CONCEPTS_HPP_
#define CONCEPTS_HPP_
/**
 * Based on http://en.cppreference.com/w/cpp/concept
 * With ressources :
 *      - http://wg21.link/p0800r0
 *      - http://wg21.link/n4674
 *      - http://wg21.link/p0734r0
 */

#include "basic/concepts.hpp"
#include "basic/traits.hpp"

#include "layout/concepts.hpp"
#include "layout/traits.hpp"

#include "utility/concepts.hpp"
#include "utility/traits.hpp"

#include <stdexcept>

namespace concepts {

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

} // namespace concepts

namespace concepts {
using namespace concepts::basic;
using namespace concepts::utility;
using namespace concepts::layout;
} // namespace concepts

namespace traits {
using namespace traits::basic;
using namespace traits::utility;
using namespace traits::layout;
} // namespace traits

#endif // CONCEPTS_HPP_
