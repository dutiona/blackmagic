#pragma once

#include <optional>
#include <tuple>
#include <utility>

namespace blackmagic::pair { inline namespace utility {


// first
struct first_t {
  template <typename Pair>
  constexpr decltype(auto) operator()(Pair&& p) const
  {
    return std::forward<Pair>(p).first;
  }
};

inline constexpr const first_t first{};


// second
struct second_t {
  template <typename Pair>
  constexpr decltype(auto) operator()(Pair&& p) const
  {
    return std::forward<Pair>(p).second;
  }
};

inline constexpr const second_t second{};


// to_tuple
struct to_tuple_t {
  template <typename Pair>
  constexpr decltype(auto) operator()(Pair&& p) const
  {
    return std::make_tuple(std::forward<Pair>(p).first, std::forward<Pair>(p).second);
  }
};

inline constexpr const to_tuple_t to_tuple{};


// from_tuple
struct from_tuple_t {
  template <typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl) const
  {
    static_assert(sizeof...(Ts) < 3, "Tuple contains too many element to be converted to a pair!");

    if constexpr (sizeof...(Ts) == 0) {
      return std::make_pair(std::nullopt, std::nullopt);
    }
    else if constexpr (sizeof...(Ts) == 1) {
      return std::make_pair(std::get<0>(tpl), std::nullopt);
    }
    else {
      return std::make_pair(std::get<0>(tpl), std::get<1>(tpl));
    }
  }
};

inline constexpr const from_tuple_t from_tuple{};


}} // namespace blackmagic::pair::utility
