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

namespace concepts {
using namespace concepts::basic;
}

namespace traits {
using namespace concepts::basic::traits;
}

#endif // CONCEPTS_HPP_