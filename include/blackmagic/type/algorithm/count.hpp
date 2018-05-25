#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

// count
template <bool... Bs>
struct count : std::integral_constant<size_t, (Bs + ...)> {
};

}} // namespace blackmagic::type::algorithm
