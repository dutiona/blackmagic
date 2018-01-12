#pragma once

#ifndef METAPROG_CPT_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
#define METAPROG_CPT_BASIC_DETAILS_CONCEPTS_IMPL_HPP_

#include "../traits.hpp"

#include "../../core.hpp"

namespace cpt::concepts::basic::details {

namespace traits = traits::basic;

// default constructible
template <typename T>
using default_constructible_impl = make_predicate<make_condition<traits::is_default_constructible_v<T>>>;

// move constructible
template <typename T>
using move_constructible_impl = make_predicate<make_condition<traits::is_move_constructible_v<T>>>;

// copy constructible
template <typename T>
using copy_constructible_impl = make_predicate<make_condition<traits::is_copy_constructible_v<T>>>;

// move assignable
template <typename T>
using move_assignable_impl = make_predicate<make_condition<traits::is_move_assignable_v<T>>>;

// copy assignable
template <typename T>
using copy_assignable_impl = make_predicate<make_condition<traits::is_copy_assignable_v<T>>>;

// destructible
template <typename T>
using destructible_impl = make_predicate<make_condition<traits::is_destructible_v<T>>>;

} // namespace cpt::concepts::basic::details

#endif // CONCEPTS_BASIC_DETAILS_CONCEPTS_IMPL_HPP_
