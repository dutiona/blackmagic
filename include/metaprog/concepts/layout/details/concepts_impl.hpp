#pragma once

#include "../traits.hpp"

#include "../../core.hpp"

namespace metaprog::concepts { inline namespace layout { namespace details {

namespace traits = metaprog::traits;

// trivially copyable
template <typename T>
using trivially_copyable_impl = make_predicate<make_condition<traits::is_trivially_copyable_v<T>>>;

// trivial
template <typename T>
using trivial_impl = make_predicate<make_condition<traits::is_trivial_v<T>>>;

// standard layout
template <typename T>
using standard_layout_impl = make_predicate<make_condition<traits::is_standard_layout_v<T>>>;

}}} // namespace metaprog::concepts::layout::details
