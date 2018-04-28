#pragma once

#include <metaprog/common/common.hpp>

#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace helpers = metaprog::common::helpers;

inline constexpr auto identity_func = [](auto&& a) { return std::forward<decltype(a)>(a); };


// at
template <typename... Ts, typename N>
constexpr decltype(auto) at(const std::tuple<Ts...>& tpl, N)
{
  if constexpr(!std::is_base_of_v<std::integral_constant, helpers::remove_cvref_t<N>>) {
    throw "Index must be an integral constant!";
  } else if constexpr(N::value > sizeof...(Ts)){
    throw "Index out of range!";
  } else {
    return std::get<N::value>(tpl);
  }
}


// equals
namespace details {
template <typename... Ts, typename... Us, size_t... I>
constexpr bool equal_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return helpers::all_of((std::get<I>(lhs) == std::get<I>(rhs))...);
}
} // namespace details
template <typename... Ts, typename... Us>
constexpr bool equals(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs)
{
  if constexpr (sizeof...(Ts) != sizeof...(Us)) {
    return false;
  }
  else {
    return details::equal_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
  }
}


// not_equals
namespace details {
template <typename... Ts, typename... Us, size_t... I>
constexpr bool not_equal_impl(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs, std::index_sequence<I...>)
{
  return helpers::any_of((std::get<I>(lhs) != std::get<I>(rhs))...);
}
} // namespace details
template <typename... Ts, typename... Us>
constexpr bool not_equals(const std::tuple<Ts...>& lhs, const std::tuple<Us...>& rhs)
{
  if constexpr (sizeof...(Ts) != sizeof...(Us)) {
    return true;
  }
  else {
    return details::not_equal_impl(lhs, rhs, std::index_sequence_for<Ts...>{});
  }
}


// all_of
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr bool all_of_impl(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::all_of(f(std::get<I>(tpl))...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl, Func&& f)
{
  return details::all_of_impl(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl)
{
  return all_of(tpl, identity_func);
}


// any_of
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr bool any_of_impl(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::any_of(f(std::get<I>(tpl))...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr bool any_of(std::tuple<Ts...> tpl, Func&& f)
{
  return details::any_of_impl(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr bool any_of(std::tuple<Ts...> tpl)
{
  return any_of(tpl, identity_func);
}


// none_of
template <typename Func, typename... Ts>
constexpr bool none_of(std::tuple<Ts...> tpl, Func&& f)
{
  return !all_of(tpl, std::forward<Func>(f));
}

template <typename... Ts>
constexpr bool none_of(std::tuple<Ts...> tpl)
{
  return !all_of(tpl);
}


// count
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr size_t count_impl(std::tuple<Ts...> tpl, Func&& f, std::index_sequence<I...>)
{
  return helpers::count(f(std::get<I>(tpl))...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr size_t count(std::tuple<Ts...> tpl, Func&& f)
{
  return details::count_impl(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
}

template <typename... Ts>
constexpr size_t count(std::tuple<Ts...> tpl)
{
  return count(tpl, identity_func);
}


// end
template <typename... Ts>
constexpr size_t end(std::tuple<Ts...>)
{
  return std::tuple_size_v<std::tuple<Ts...>>;
}


// front
template <typename... Ts>
constexpr decltype(auto) front(const std::tuple<Ts...>& tpl)
{
  if constexpr (sizeof...(Ts) == 0) {
    throw "Tuple is empty!";
  }
  else {
    return std::get<0>(tpl);
  }
}


// back
template <typename... Ts>
constexpr decltype(auto) back(const std::tuple<Ts...>& tpl)
{
  if constexpr (sizeof...(Ts) == 0) {
    throw "Tuple is empty!";
  }
  else {
    return std::get<sizeof...(Ts) - 1>(tpl);
  }
}


// push_front
template <typename T, typename... Ts>
constexpr auto push_front(const std::tuple<Ts...>& tpl, T&& e)
{
  return std::tuple_cat(std::make_tuple(std::forward<T>(e)), tpl);
}


// push_back
template <typename T, typename... Ts>
constexpr auto push_back(const std::tuple<Ts...>& tpl, T&& e)
{
  return std::tuple_cat(tpl, std::make_tuple(std::forward<T>(e)));
}


// pop_front
namespace details {
template <typename T, typename... Ts, size_t I, size_t... J>
constexpr auto pop_front_impl(const std::tuple<T, Ts...>& tpl, std::index_sequence<I, J...>)
{
  return std::make_tuple(std::get<J>(tpl)...);
}
} // namespace details

template <typename... Ts>
constexpr auto pop_front(const std::tuple<Ts...>& tpl)
{
  if constexpr (sizeof...(Ts) == 0) {
    throw "Tuple is empty!";
  }
  else {
    return details::pop_front_impl(tpl, std::index_sequence_for<Ts...>{});
  }
}


// pop_back
namespace details {
template <typename... Ts, size_t... I>
constexpr auto pop_back_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<I>(tpl)...);
}
} // namespace details

template <typename... Ts>
constexpr auto pop_back(const std::tuple<Ts...>& tpl)
{
  if constexpr (sizeof...(Ts) == 0) {
    throw "Tuple is empty!";
  }
  else {
    return details::pop_back_impl(tpl, std::make_index_sequence<sizeof...(Ts) - 1>{});
  }
}


// rotate_left
template <typename... Ts>
constexpr auto rotate_left(const std::tuple<Ts...>& tpl)
{
  return push_back(pop_front(tpl), front(tpl));
}


// rotate_right
template <typename... Ts>
constexpr auto rotate_right(const std::tuple<Ts...>& tpl)
{
  return push_front(pop_back(tpl), back(tpl));
}


// reverse
namespace details {
template <typename... Ts, typename... Us>
constexpr auto reverse_impl(const std::tuple<Ts...>& tpl, const std::tuple<Us...>& ret)
{
  if constexpr (sizeof...(Ts) == 0) {
    return ret;
  }
  else {
    static_assert(sizeof...(Ts) > 0);
    return reverse_impl(pop_front(tpl), push_front(ret, front(tpl)));
  }
}
} // namespace details

template <typename... Ts>
constexpr auto reverse(const std::tuple<Ts...>& tpl)
{
  return details::reverse_impl(tpl, std::tuple<>());
}


// for_each
namespace details {
template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  (f(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}

template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr void for_each_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  (f(std::get<I>(tpl), std::forward<Args>(args)...), ...);
}
} // namespace details

template <typename Func, typename... Args, typename... Ts>
constexpr void for_each(std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f), std::forward<Args>(args)...);
}

template <typename Func, typename... Args, typename... Ts>
constexpr void for_each(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f), std::forward<Args>(args)...);
}


// transform
namespace details {
template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f,
                                        Args&&... args)
{
  return std::make_tuple(f(std::get<I>(tpl), std::forward<Args>(args)...)...);
}
} // namespace details

template <typename Func, typename... Args, typename... Ts>
constexpr auto transform(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
                                 std::forward<Args>(args)...);
}


// accumulate
namespace details {
template <typename T, typename Func, typename... Args, typename... Ts, size_t... I>
constexpr T accumulate_impl(T&& init, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  ((init = f(std::forward<T>(init), std::get<I>(tpl), std::forward<Args>(args)...)), ...);
  return init;
}
} // namespace details

template <typename T, typename Func, typename... Args, typename... Ts>
constexpr auto accumulate(T&& init, std::tuple<Ts...> tpl, Func&& f, Args&&... args)
{
  return details::accumulate_impl(std::forward<T>(init), tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
                                  std::forward<Args>(args)...);
}

namespace details {
template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr size_t count_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  size_t ret = 0;
  ((ret += f(std::get<I>(tpl), std::forward<Args>(args)...) ? 1 : 0), ...);
  return ret;
}
} // namespace details

namespace details {
template <typename Func, typename... Args, typename... Ts>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<>, Func&&, Args&&...)
{
  return end(tpl);
}

template <typename Func, typename... Args, typename... Ts, size_t I, size_t... J>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I, J...>, Func&& f, Args&&... args)
{
  return !f(std::get<I>(tpl), std::forward<Args>(args)...)
           ? find_if_impl(tpl, std::index_sequence<J...>{}, std::forward<Func>(f), std::forward<Args>(args)...)
           : I;
}
} // namespace details

namespace details {
template <typename... Ts, size_t... I>
constexpr auto make_indexes_to_keep(const std::tuple<Ts...>& elems_to_keep, std::index_sequence<I...>)
{
  (void) elems_to_keep;
  /*
  cstxpr::vector<size_t, sizeof...(Ts)> indexes{};
  size_t index = 0;
  ((bool(std::get<I>(elems_to_keep)) ? void(indexes.push_back(index++)) : void(index++)), ...);
   */
  return 0;
}

template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) filter_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  (void) tpl;
  (void) f;
  ((void) args, ...);

  const auto elems_to_keep   = transform(tpl, std::forward<Func>(f), std::forward<Args>(args)...);
  const auto indexes_to_keep = make_indexes_to_keep(elems_to_keep, std::index_sequence_for<Ts...>{});
  return indexes_to_keep;
  // constexpr auto indices = filter_indices;
}
} // namespace details

/*
template <typename Func, typename K, typename V, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) replace_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f,
                                    const std::pair<K, V>& e, Args&&... args)
{
  return std::make_tuple((f(std::get<I>(tpl), std::forward<Args>(args)...) ? e : std::get<I>(tpl))...);
}

template <typename Func, typename... Args, typename... Ts, size_t... I>
constexpr decltype(auto) copy_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f, Args&&... args)
{
  return std::tuple_cat(
    (f(std::get<I>(tpl), std::forward<Args>(args)...) ? std::make_tuple(std::get<I>(tpl)) : std::make_tuple())...);
}

template <typename Func, typename... Args, typename... Us>
constexpr decltype(auto) remove_if_impl(const std::tuple<>&, const std::tuple<Us...>& ret, std::index_sequence<>,
Func&&, Args&&...)
{
  return ret;
}

template <typename Func, typename... Args, typename T, typename... Ts, size_t I, size_t... J, typename... Us>
constexpr decltype(auto) remove_if_impl(const std::tuple<T, Ts...>& tpl, const std::tuple<Us...>& ret,
std::index_sequence<I, J...>, Func&& f, Args&&... args)
{
  return remove_if_impl(std::make_tuple(std::get<J>(tpl)...),
                   push_back_if(ret, std::get<I>(tpl), std::forward<Func>(f), std::forward<Args>(args)...),
                   std::index_sequence_for<Ts...>{},
                   std::forward<Func>(f), std::forward<Args>(args)...
  );
}
*/


template <typename Func, typename... Args, typename... Ts>
constexpr decltype(auto) count_if(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::count_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
                                std::forward<Args>(args)...);
}

template <typename Func, typename... Args, typename... Ts>
constexpr decltype(auto) find_if(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::find_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
                               std::forward<Args>(args)...);
}

template <typename Func, typename... Args, typename... Ts>
constexpr decltype(auto) filter(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::filter_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
                              std::forward<Args>(args)...);
}

/*
template <typename Func, typename K, typename V, typename... Args, typename... Ts>
constexpr decltype(auto) replace_if(const std::tuple<Ts...>& tpl, Func&& f, const std::pair<K, V>& e, Args&&... args)
{
  return details::replace_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f), e,
                             std::forward<Args>(args)...);
}

template <typename Func, typename... Args, typename... Ts>
constexpr decltype(auto) remove_if(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::remove_if_impl(tpl, std::tuple<>(), std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
std::forward<Args>(args)...);
}

template <typename Func, typename... Args, typename... Ts>
constexpr decltype(auto) copy_if(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::copy_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f),
std::forward<Args>(args)...);
}

template <typename T>
constexpr decltype(auto) unique(const std::tuple<T>& tpl)
{
  return tpl;
}

template <typename T, typename... Ts>
constexpr decltype(auto) unique(const std::tuple<T, Ts...>& tpl)
{
  return std::tuple_cat(std::get<0>(tpl),
                        unique(remove_if(tpl, [cur = std::get<0>(tpl)](auto e) { return e == cur; })));
}
*/

}} // namespace metaprog::tuple::algorithm
