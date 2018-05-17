#pragma once

#include <type_traits>

namespace blackmagic::type { inline namespace algorithm {

// none_of
template <bool... Bs>
struct none_of : std::conjunction<std::bool_constant<!Bs>...> {
};

}} // namespace blackmagic::type::algorithm
