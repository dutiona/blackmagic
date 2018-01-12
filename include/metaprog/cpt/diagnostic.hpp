#pragma once

#ifndef METAPROG_CPT_DIAGNOSTIC_HPP_
#define METAPROG_CPT_DIAGNOSTIC_HPP_

#include "basic/diagnostic.hpp"
#include "iterator/diagnostic.hpp"
#include "layout/diagnostic.hpp"
#include "library/diagnostic.hpp"
#include "utility/diagnostic.hpp"

namespace cpt::diagnostic {

using namespace basic::diagnostic;
using namespace iterator::diagnostic;
using namespace layout::diagnostic;
using namespace library::diagnostic;
using namespace utility::diagnostic;

} // namespace cpt::diagnostic

// public API
namespace concept_diagnostic_traits {
using namespace cpt::diagnostic;
}

#endif // METAPROG_CPT_DIAGNOSTIC_HPP_
