#pragma once

#include "../engine.hpp"

#include <type_traits>

namespace metaprog::concepts { inline namespace core { namespace details {

template <typename... Ts>
struct same_predicate : make_predicate<std::true_type> {
};

template <typename T, typename... Us>
struct same_predicate<T, Us...> : make_predicate<std::is_same<T, Us>...> {
};

template <typename From, typename To>
using implicitly_convertible_to_predicate = make_predicate<std::is_convertible<From, To>>;

template <typename From, typename To>
using explicitly_convertible_to_predicate =
  make_predicate<valid_expr<decltype((void) static_cast<To>(std::declval<From(*)()>()()), 42)>>;

}}} // namespace metaprog::concepts::core::details
