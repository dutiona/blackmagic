#pragma once

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

// all_of
template <bool... Bs>
struct all_of : std::conjunction<std::bool_constant<Bs>...> {
};

}} // namespace blackmagic::type::algorithm
