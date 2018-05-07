#pragma once

#include "helpers.hpp"

#include <ostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>

namespace metaprog::tuple {

struct print_all_t {
  template <typename... Ts>
  void operator()(const std::tuple<Ts...>& tpl, std::ostream& os, size_t idx = 0, size_t padding = 0) const;
};

inline constexpr print_all_t print_all{};

namespace details {

template <typename... Ts, size_t I, size_t... J>
void print_all_impl_(const std::tuple<Ts...>& tpl, std::ostream& os, size_t idx, size_t padding,
                     std::index_sequence<I, J...>)
{
  if constexpr (helpers::is_tuple_v<std::decay_t<decltype(std::get<I>(tpl))>>) {
    (os << std::string(padding, '\t') << "[" << idx << "] <"
        << "nested tuple"
        << "> : \n");
    print_all(std::get<I>(tpl), os, 0, padding + 1);
  }
  else {
    (os << std::string(padding, '\t') << "[" << idx << "] <" << typeid(std::get<I>(tpl)).name()
        << "> : " << std::get<I>(tpl) << '\n');
  }

  if constexpr (sizeof...(J) > 0) {
    print_all(std::make_tuple(std::get<J>(tpl)...), os, idx + 1, padding);
  }
}

template <typename... Ts, size_t... I>
void print_all_impl(const std::tuple<Ts...>& tpl, std::ostream& os, size_t idx, size_t padding,
                    std::index_sequence<I...>)
{
  if constexpr (sizeof...(Ts) > 0) {
    print_all_impl_(tpl, os, idx, padding, std::index_sequence<I...>{});
  }
  else {
    os << std::string(padding, '\t') << "!empty!\n";
  }
}

} // namespace details

template <typename... Ts>
void print_all_t::operator()(const std::tuple<Ts...>& tpl, std::ostream& os, size_t idx, size_t padding) const
{
  details::print_all_impl(tpl, os, idx, padding, std::index_sequence_for<Ts...>{});
}

} // namespace metaprog::tuple
