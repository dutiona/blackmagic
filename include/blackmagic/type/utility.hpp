#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::type { inline namespace utility {

// all_of
template <bool... Bs>
struct all_of : std::conjunction<std::bool_constant<Bs>...> {
};


// any_of
template <bool... Bs>
struct any_of : std::disjunction<std::bool_constant<Bs>...> {
};


// none_of
template <bool... Bs>
struct none_of : std::conjunction<std::bool_constant<!Bs>...> {
};


// count
template <bool... Bs>
struct count : std::integral_constant<size_t, (Bs + ...)> {
};

}} // namespace blackmagic::type::utility
