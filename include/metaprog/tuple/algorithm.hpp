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
#include "equals.hpp"
#include "find_if.hpp"
#include "fold.hpp"
#include "fold_left.hpp"
#include "fold_right.hpp"
#include "for_each.hpp"
#include "front.hpp"
#include "length.hpp"
#include "merge.hpp"
#include "none_of.hpp"
#include "not_equals.hpp"
#include "pop_back.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"
#include "push_front.hpp"
#include "remove_if.hpp"
#include "repeat.hpp"
#include "reverse.hpp"
#include "rotate.hpp"
#include "rotate_left.hpp"
#include "rotate_right.hpp"
#include "transform.hpp"
#include "unique.hpp"
#include "unpack.hpp"
#include "zip.hpp"

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