#pragma once

#include <array>
#include <tuple>
#include <utility>

namespace metaprog::tuple { inline namespace algorithm {

namespace details {

template <typename Func, typename... Ts, size_t... I>
constexpr decltype(auto) unpack_impl(const std::tuple<Ts...>& tpl, Func&& f, std::index_sequence<I...>)
{
  return std::forward<Func>(f)(std::get<I>(tpl)...);
}

template <typename Func, typename T, size_t N, size_t... I>
constexpr decltype(auto) unpack_impl(const std::array<T, N>& arr, Func&& f, std::index_sequence<I...>)
{
  return std::forward<Func>(f)(arr[I]...);
}

template <typename Func, typename T, size_t N, size_t... I>
constexpr decltype(auto) unpack_impl(T (&arr)[N], Func&& f, std::index_sequence<I...>)
{
  return std::forward<Func>(f)(arr[I]...);
}

} // namespace details

struct unpack_t {
  template <typename Func, typename... Ts>
  constexpr decltype(auto) operator()(const std::tuple<Ts...>& tpl, Func&& f) const
  {
    return details::unpack_impl(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
  }

  template <typename Func, typename T, size_t N>
  constexpr decltype(auto) operator()(const std::array<T, N>& arr, Func&& f) const
  {
    return details::unpack_impl(arr, std::forward<Func>(f), std::make_index_sequence<N>{});
  }

  template <typename Func, typename T, size_t N>
  constexpr decltype(auto) operator()(T (&arr)[N], Func&& f) const
  {
    return details::unpack_impl(arr, std::forward<Func>(f), std::make_index_sequence<N>{});
  }
};

inline constexpr unpack_t unpack{};

}} // namespace blackmagic::tuple::algorithm
