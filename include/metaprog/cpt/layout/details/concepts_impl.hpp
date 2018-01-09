#pragma once

#ifndef METAPROG_CPT_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
#define METAPROG_CPT_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_

#include "../traits.hpp"

#include "../../verif.hpp"

#include <type_traits>

namespace cpt { namespace concepts { namespace layout { namespace details {

namespace traits = traits::layout;

// trivially copyable
template <typename T>
using trivially_copyable_impl = make_predicate<make_condition<traits::is_trivially_copyable_v<T>>>;

// trivial
template <typename T>
using trivial_impl = make_predicate<make_condition<traits::is_trivial_v<T>>>;

// standard layout
template <typename T>
using standard_layout_impl = make_predicate<make_condition<traits::is_standard_layout_v<T>>>;

}}}} // namespace cpt::concepts::layout::details

#endif // METAPROG_CPT_LAYOUT_DETAILS_CONCEPTS_IMPL_HPP_
