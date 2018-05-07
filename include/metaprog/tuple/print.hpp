#pragma once

#include <ostream>
#include <tuple>
#include <typeinfo>
#include <utility>

namespace metaprog::tuple {

namespace details {

template <typename... Ts, size_t... I>
void print_impl(const std::tuple<Ts...>& tpl, std::ostream& os, std::index_sequence<I...>)
{
  ((os << "[" << I << "] <" << typeid(std::get<I>(tpl)).name() << "> : " << std::get<I>(tpl) << '\n'), ...);
}

} // namespace details

struct print_t {
  template <typename... Ts>
  void operator()(const std::tuple<Ts...>& tpl, std::ostream& os) const
  {
    details::print_impl(tpl, os, std::index_sequence_for<Ts...>{});
  }
};

inline constexpr print_t print{};

} // namespace metaprog::tuple
