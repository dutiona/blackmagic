#pragma once

#include "accumulate.hpp"
#include "all_of.hpp"
#include "any_of.hpp"
#include "at.hpp"
#include "back.hpp"
#include "copy_if.hpp"
#include "count.hpp"
#include "count_if.hpp"
#include "end.hpp"
#include "equal.hpp"
#include "find_if.hpp"
#include "fold.hpp"
#include "fold_left.hpp"
#include "fold_right.hpp"
#include "for_each.hpp"
#include "front.hpp"
#include "none_of.hpp"
#include "not_equal.hpp"
#include "pop_back.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"
#include "push_front.hpp"
#include "remove_if.hpp"
#include "reverse.hpp"
#include "rotate.hpp"
#include "rotate_left.hpp"
#include "rotate_right.hpp"
#include "transform.hpp"
#include "unique.hpp"
#include "unpack.hpp"


namespace common_helpers = metaprog::common::helpers;

static_assert(metaprog::tuple::equals(std::make_tuple(2.0, 48.0),
                                      metaprog::tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                 common_helpers::trait<std::is_integral>)));
static_assert(metaprog::tuple::equals(std::make_tuple(2.0, 48.0),
                                      metaprog::tuple::remove_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                                 common_helpers::trait<std::is_same, int>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 3, 55),
                                      metaprog::tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                               common_helpers::trait<std::is_integral>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 3, 55),
                                      metaprog::tuple::copy_if(std::make_tuple(1, 2.0, 3, 48.0, 55),
                                                               common_helpers::trait<std::is_same, int>)));

static_assert(metaprog::tuple::equals(std::make_tuple(1, 2.0),
                                      metaprog::tuple::unique(std::make_tuple(1, 2.0, 3, 48.0, 55))));

// TODO/FIXME
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