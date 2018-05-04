#pragma once

#include "../type/type.hpp"

#include <tuple>

namespace metaprog::tuple { inline namespace algorithm {

namespace type = metaprog::type;

namespace details {

struct back_t {
  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

    return std::get<type::minus<type::size_t_<sizeof...(Ts)>, type::int_<1>>::value>(tpl);
  }
};

} // namespace details

inline constexpr details::back_t back{};

}} // namespace metaprog::tuple::algorithm
