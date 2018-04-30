#pragma once

#include <metaprog/common/common.hpp>

#include <array>
#include <tuple>
#include <type_traits>

namespace metaprog::tuple { inline namespace algorithm {

namespace helpers = metaprog::common::helpers;

struct identity_func_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& t) const
  {
    return std::forward<T>(t);
  }
};
inline constexpr const identity_func_t identity_func{};


// tuple_remove_const
template <typename... Ts>
using tuple_remove_const = std::tuple<std::remove_const_t<Ts>...>;
// tuple_remove_volatile
template <typename... Ts>
using tuple_remove_volatile = std::tuple<std::remove_volatile_t<Ts>...>;
// tuple_remove_cv
template <typename... Ts>
using tuple_remove_cv = std::tuple<std::remove_cv_t<Ts>...>;
// tuple_remove_reference
template <typename... Ts>
using tuple_remove_reference = std::tuple<std::remove_reference_t<Ts>...>;
// tuple_remove_cvref
template <typename... Ts>
using tuple_remove_cvref = std::tuple<helpers::remove_cvref_t<Ts>...>;
// tuple_decay
template <typename... Ts>
using tuple_decay = std::tuple<std::decay_t<Ts>...>;


// at
template <typename... Ts, typename N>
constexpr decltype(auto) at(const std::tuple<Ts...>& tpl, N)
{
  static_assert(std::is_base_of_v<std::integral_constant, helpers::remove_cvref_t<N>>,
                "Index must be an integral constant!");
  static_assert(N::value < sizeof...(Ts) && N::value >= 0, "Index out of range!");

  return std::get<N::value>(tpl);
}


// unpack
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr decltype(auto) unpack_impl(const std::tuple<Ts...>& tpl, Func&& f, std::index_sequence<I...>)
{
  return f(std::get<I>(tpl)...);
}

template <typename Func, typename T, size_t N, size_t... I>
constexpr decltype(auto) unpack_impl(T (&arr)[N], Func&& f, std::index_sequence<I...>)
{
  return f(arr[I]...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr decltype(auto) unpack(const std::tuple<Ts...>& tpl, Func&& f)
{
  return details::unpack_impl(tpl, std::forward<Func>(f), std::index_sequence_for<Ts...>{});
}

template <typename Func, typename T, size_t N>
constexpr decltype(auto) unpack(T (&arr)[N], Func&& f)
{
  return details::unpack_impl(arr, std::forward<Func>(f), std::make_index_sequence<N>{});
}


// transform
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr auto transform_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  return std::make_tuple(f(std::get<I>(tpl))...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr auto transform(const std::tuple<Ts...>& tpl, Func&& f)
{
  return details::transform_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
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
template <typename Func, typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl, Func&& f)
{
  return unpack(transform(tpl, std::forward<Func>(f)), [](auto... e) { return helpers::all_of(e...); });
}

template <typename... Ts>
constexpr bool all_of(std::tuple<Ts...> tpl)
{
  return all_of(tpl, identity_func);
}


// any_of
template <typename Func, typename... Ts>
constexpr bool any_of(std::tuple<Ts...> tpl, Func&& f)
{
  return unpack(transform(tpl, std::forward<Func>(f)), [](auto... e) { return helpers::any_of(e...); });
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
template <typename Func, typename... Ts>
constexpr size_t count(std::tuple<Ts...> tpl, Func&& f)
{
  return unpack(transform(tpl, std::forward<Func>(f)), [](auto... e) { return helpers::count(e...); });
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
  static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

  return std::get<0>(tpl);
}


// back
template <typename... Ts>
constexpr decltype(auto) back(const std::tuple<Ts...>& tpl)
{
  static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

  return std::get<sizeof...(Ts) - 1>(tpl);
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
  static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

  return details::pop_front_impl(tpl, std::index_sequence_for<Ts...>{});
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
  static_assert(sizeof...(Ts) > 0, "Tuple is empty!");

  return details::pop_back_impl(tpl, std::make_index_sequence<sizeof...(Ts) - 1>{});
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


// fold_left
namespace details {
template <typename Func, typename T, size_t I>
constexpr auto fold_left_impl(const std::tuple<T>& tpl, Func&&, std::index_sequence<I>)
{
  return std::get<I>(tpl);
}

template <typename Func, typename T, typename U, typename... Vs, size_t I, size_t J, size_t... K>
constexpr decltype(auto) fold_left_impl(const std::tuple<T, U, Vs...>& tpl, Func&& f, std::index_sequence<I, J, K...>)
{
  return fold_left_impl(push_front(std::make_tuple(std::get<K>(tpl)...), f(std::get<I>(tpl), std::get<J>(tpl))),
                        std::forward<Func>(f), std::make_index_sequence<sizeof...(Vs) + 1>{});
}
} // namespace details

template <typename Func, typename... Ts, typename... Args>
constexpr decltype(auto) fold_left(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return details::fold_left_impl(std::tuple_cat(std::make_tuple(std::forward<Args>(args)...), tpl),
                                 std::forward<Func>(f), std::index_sequence_for<Args..., Ts...>{});
}


// fold_right
template <typename Func, typename... Ts, typename... Args>
constexpr decltype(auto) fold_right(const std::tuple<Ts...>& tpl, Func&& f, Args&&... args)
{
  return fold_left(std::tuple_cat(reverse(std::make_tuple(std::forward<Args>(args)...)), reverse(tpl)),
                   std::forward<Func>(f));
}


// for_each
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr void for_each_impl(std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  (f(std::get<I>(tpl)), ...);
}

template <typename Func, typename... Ts, size_t... I>
constexpr void for_each_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  (f(std::get<I>(tpl)), ...);
}
} // namespace details

template <typename Func, typename... Ts>
constexpr void for_each(std::tuple<Ts...>& tpl, Func&& f)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
}

template <typename Func, typename... Ts>
constexpr void for_each(const std::tuple<Ts...>& tpl, Func&& f)
{
  details::for_each_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
}


// accumulate
namespace details {
template <typename T, typename Func, typename... Ts, size_t... I>
constexpr T accumulate_impl(T&& init, const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  ((init = f(std::forward<T>(init), std::get<I>(tpl))), ...);
  return init;
}
} // namespace details

template <typename T, typename Func, typename... Ts>
constexpr auto accumulate(T&& init, std::tuple<Ts...> tpl, Func&& f)
{
  return details::accumulate_impl(std::forward<T>(init), tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
}


// count_if
namespace details {
template <typename Func, typename... Ts, size_t... I>
constexpr size_t count_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f)
{
  size_t ret = 0;
  ((ret += f(std::get<I>(tpl)) ? 1 : 0), ...);
  return ret;
}
} // namespace details

template <typename Func, typename... Ts>
constexpr decltype(auto) count_if(const std::tuple<Ts...>& tpl, Func&& f)
{
  return details::count_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
}


// find_if
namespace details {
template <typename Func, typename... Ts>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<>, Func&&)
{
  return end(tpl);
}

template <typename Func, typename... Ts, size_t I, size_t... J>
constexpr size_t find_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I, J...>, Func&& f)
{
  return !f(std::get<I>(tpl)) ? find_if_impl(tpl, std::index_sequence<J...>{}, std::forward<Func>(f)) : I;
}
} // namespace details

template <typename Func, typename... Ts>
constexpr decltype(auto) find_if(const std::tuple<Ts...>& tpl, Func&& f)
{
  return details::find_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f));
}


// filter
namespace details {
template <bool... bools>
struct filter_indexes {
  static constexpr auto make_indexes()
  {
    constexpr bool             b[] = {bools..., false};
    constexpr std::size_t      N   = helpers::count(bools..., false);
    std::array<std::size_t, N> indexes{};
    auto                       keep = indexes.begin();
    for (std::size_t i = 0; i < sizeof...(bools); ++i)
      if (b[i])
        *keep++ = i;
    return indexes;
  }
  static constexpr auto indexes = make_indexes();
};
template <template <typename...> class Pred, typename... Us>
struct make_filter_indexes {
  template <typename... Ts>
  auto operator()(Ts&&...) const -> filter_indexes<static_cast<bool>(Pred<Us..., std::decay_t<Ts>>::value)...>
  {
    return {};
  }
};
template <typename Indexes, typename... Ts, size_t... I>
constexpr auto build_filtered_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<Indexes::indexes[I]>(tpl)...);
}
template <template <typename...> class Pred, typename... Us, typename... Ts, size_t... I>
constexpr decltype(auto) filter_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_filter_indexes<Pred, Us...>{}));
  return build_filtered_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}
} // namespace details

template <template <typename...> class Pred, typename... Us, typename... Ts>
constexpr auto filter(const std::tuple<Ts...>& tpl)
{
  return details::filter_impl<Pred, Us...>(tpl, std::index_sequence_for<Ts...>{});
}


// remove_if
namespace details {
template <template <typename...> class Pred, typename... Us>
struct make_remove_if_indexes {
  template <typename... Ts>
  auto operator()(Ts&&...) const -> filter_indexes<static_cast<bool>(std::negation_v<Pred<Us..., std::decay_t<Ts>>>)...>
  {
    return {};
  }
};
template <typename Indexes, typename... Ts, size_t... I>
constexpr auto build_removed_tuple(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  return std::make_tuple(std::get<Indexes::indexes[I]>(tpl)...);
}
template <template <typename...> class Pred, typename... Us, typename... Ts, size_t... I>
constexpr decltype(auto) remove_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  using indexes_t = decltype(unpack(tpl, make_remove_if_indexes<Pred, Us...>{}));
  return build_removed_tuple<indexes_t>(tpl, std::make_index_sequence<indexes_t::indexes.size()>{});
}
} // namespace details

template <template <typename...> class Pred, typename... Us, typename... Ts>
constexpr auto remove_if(const std::tuple<Ts...>& tpl)
{
  return details::remove_if_impl<Pred, Us...>(tpl, std::index_sequence_for<Ts...>{});
}


// unique
template <typename... Ts>
constexpr auto unique(const std::tuple<Ts...>& tpl);

namespace details {
template <typename... Ts, size_t... I>
constexpr auto unique_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>)
{
  if constexpr (sizeof...(Ts) == 0) {
    return tpl;
  }
  else {
    return push_front(unique(remove_if<std::is_same, std::decay_t<decltype(front(tpl))>>(pop_front(tpl))), front(tpl));
  }
}
} // namespace details

template <typename... Ts>
constexpr auto unique(const std::tuple<Ts...>& tpl)
{
  return details::unique_impl(tpl, std::index_sequence_for<Ts...>{});
}

/*
template <typename Func, typename K, typename V, typename... Ts, size_t... I>
constexpr decltype(auto) replace_if_impl(const std::tuple<Ts...>& tpl, std::index_sequence<I...>, Func&& f,
                                    const std::pair<K, V>& e)
{
  return std::make_tuple((f(std::get<I>(tpl)) ? e : std::get<I>(tpl))...);
}


template <typename Func, typename K, typename V, typename... Ts>
constexpr decltype(auto) replace_if(const std::tuple<Ts...>& tpl, Func&& f, const std::pair<K, V>& e)
{
  return details::replace_if_impl(tpl, std::index_sequence_for<Ts...>{}, std::forward<Func>(f), e);
}
*/

}} // namespace metaprog::tuple::algorithm
