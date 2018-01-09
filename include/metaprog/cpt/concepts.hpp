#pragma once

#ifndef METAPROG_CPT_CONCEPTS_HPP_
#define METAPROG_CPT_CONCEPTS_HPP_

#include "basic/concepts.hpp"
#include "iterator/concepts.hpp"
#include "layout/concepts.hpp"
#include "library/concepts.hpp"
#include "utility/concepts.hpp"

namespace cpt { namespace concepts {

using namespace concepts::basic;
using namespace concepts::iterator;
using namespace concepts::layout;
using namespace concepts::library;
using namespace concepts::utility;

}} // namespace cpt::concepts

#endif // METAPROG_CPT_CONCEPTS_HPP_
