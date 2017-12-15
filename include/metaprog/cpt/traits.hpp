#pragma once

#ifndef METAPROG_CPT_TRAITS_HPP_
#define METAPROG_CPT_TRAITS_HPP_

#include "basic/traits.hpp"
#include "iterator/traits.hpp"
#include "layout/traits.hpp"
#include "library/traits.hpp"
#include "utility/traits.hpp"

namespace cpt { namespace traits {

using namespace traits::basic;
using namespace traits::utility;
using namespace traits::layout;
using namespace traits::library;
using namespace traits::iterator;

}} // namespace cpt::traits

#endif // METAPROG_CPT_TRAITS_HPP_
