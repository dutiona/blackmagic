#pragma once

#include <metaprog/common/common.hpp>

#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace helpers = metaprog::common::helpers;

namespace details {

inline constexpr auto identity_func = [](auto&& a) { return std::forward<decltype(a)>(a); };

template <typename Func, typename... Ts, size_t... I>
constexpr bool all_of(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::all_of(std::forward<Func>(f)(std::get<I>(tpl))...);
}

template <typename Func, typename... Ts, size_t... I>
constexpr bool any_of(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::any_of(std::forward<Func>(f)(std::get<I>(tpl))...);
}

template <typename Func, typename... Ts, size_t... I>
constexpr bool count(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::count(std::forward<Func>(f)(std::get<I>(tpl))...);
}

} // namespace details

template <typename Func, typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl, Func&& f)
{
  return details::all_of(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl)
{
  return all_of(tpl, details::identity_func);
}

template <typename F, typename... Ts>
constexpr bool any_of(std::tuple<Ts...> tpl, F&& func)
{
  return details::any_of(tpl, std::forward<F>(func), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool any_of(std::tuple<Ts...> tpl)
{
  return any_of(tpl, details::identity_func);
}

template <typename F, typename... Ts>
constexpr bool none_of(std::tuple<Ts...> tpl, F&& func)
{
  return !all_of(tpl, std::forward<F>(func));
}

template <typename... Ts>
constexpr bool none_of(std::tuple<Ts...> tpl)
{
  return !all_of(tpl);
}

template <typename F, typename... Ts>
constexpr bool count(std::tuple<Ts...> tpl, F&& func)
{
  return details::count(tpl, std::forward<F>(func), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool count(std::tuple<Ts...> tpl)
{
  return count(tpl, details::identity_func);
}

template <typename... Ts>
constexpr size_t end(std::tuple<Ts...>)
{
  return std::tuple_size_v<std::tuple<Ts...>>;
}

// for_each/transform/accumulate/count_if/find_if for tuples
namespace details {

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  (std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  (std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func,
                                        Args&&... args)
{
  return std::make_tuple(std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...)...);
}

template <typename T, typename F, typename... Args, typename... Ts, size_t... I>
constexpr T accumulate_impl(T&& init, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  ((init = std::forward<F>(func)(std::forward<T>(init), std::get<I>(tpl), std::forward<Args>(args)...)), ...);
  return init;
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr size_t count_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  size_t ret = 0;
  ((ret += std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...) ? 1 : 0), ...);
  return ret;
}

template <typename F, typename... Args, typename... Ts>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<>, F&&, Args&&...)
{
  return end(tpl);
}

template <typename F, typename... Args, typename... Ts, size_t I, size_t... J>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I, J...>, F&& func, Args&&... args)
{
  return !std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...)
           ? find_if_impl(tpl, std::index_sequence<J...>{}, std::forward<F>(func), std::forward<Args>(args)...)
           : I;
}

template <typename F, typename K, typename V, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) replace_if(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func,
                                    const std::pair<K, V>& e, Args&&... args)
{
  return std::make_tuple(
    (std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...) ? e : std::get<I>(tpl))...);
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) remove_if(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  return std::tuple_cat((!std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...)
                           ? std::make_tuple(std::get<I>(tpl))
                           : std::make_tuple())...);
}

template <typename F, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) copy_if(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, F&& func, Args&&... args)
{
  return std::tuple_cat((std::forward<F>(func)(std::get<I>(tpl), std::forward<Args>(args)...)
                           ? std::make_tuple(std::get<I>(tpl))
                           : std::make_tuple())...);
}

} // namespace details

template <typename F, typename... Args, typename... Ts>
constexpr void for_each(std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr void for_each(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) transform(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                 std::forward<Args>(args)...);
}

template <typename T, typename F, typename... Args, typename... Ts>
constexpr decltype(auto) accumulate(T&& init, std::tuple<Ts...> tpl, F&& func, Args&&... args)
{
  return details::accumulate_impl(std::forward<T>(init), tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                  std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) count_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::count_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                                std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) find_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::find_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func),
                               std::forward<Args>(args)...);
}

template <typename F, typename K, typename V, typename... Args, typename... Ts>
constexpr decltype(auto) replace_if(const std::tuple<Ts...>& tpl, F&& func, const std::pair<K, V>& e, Args&&... args)
{
  return details::replace_if(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), e,
                             std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) remove_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::remove_if(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}

template <typename F, typename... Args, typename... Ts>
constexpr decltype(auto) copy_if(const std::tuple<Ts...>& tpl, F&& func, Args&&... args)
{
  return details::copy_if(tpl, std::index_sequence_for<Ts...>{}, std::forward<F>(func), std::forward<Args>(args)...);
}

template <typename K, typename V, typename... Ts>
constexpr decltype(auto) push_back(const std::tuple<Ts...>& tpl, const std::pair<K, V>& e)
{
  return std::tuple_cat(tpl, std::make_tuple(e));
}

}} // namespace metaprog::tuple::algorithm
