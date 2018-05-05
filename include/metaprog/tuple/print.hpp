#pragma once

#include <iostream>
#include <tuple>
#include <typeinfo>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename... Ts, size_t... I>
void print_tuple(const std::tuple<Ts...>& tpl, std::ostream& os, std::index_sequence<I...>)
{
  ((os << "[" << I << "] <" << typeid(std::get<I>(tpl)).name() << "> : " << std::get<I>(tpl) << '\n'), ...);
}

struct print_t {
  template <typename... Ts>
  void operator()(const std::tuple<Ts...>& tpl, std::ostream& os) const
  {
    print_tuple(tpl, os, std::index_sequence_for<Ts...>{});
  }
};

} // namespace details

inline constexpr details::print_t print{};

}} // namespace metaprog::tuple::algorithm
