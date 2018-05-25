#pragma once

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

// any_of
template <bool... Bs>
struct any_of : std::disjunction<std::bool_constant<Bs>...> {
};

}} // namespace blackmagic::type::algorithm
