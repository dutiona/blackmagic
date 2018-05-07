#pragma once

#include "accumulate.hpp"
#include "all.hpp"
#include "all_of.hpp"
#include "any.hpp"
#include "any_of.hpp"
#include "at.hpp"
#include "back.hpp"
#include "contains.hpp"
#include "copy.hpp"
#include "copy_if.hpp"
#include "count.hpp"
#include "count_if.hpp"
#include "end.hpp"
#include "equals.hpp"
#include "find.hpp"
#include "find_if.hpp"
#include "fold.hpp"
#include "fold_left.hpp"
#include "fold_right.hpp"
#include "for_each.hpp"
#include "front.hpp"
#include "length.hpp"
#include "merge.hpp"
#include "none.hpp"
#include "none_of.hpp"
#include "not_equals.hpp"
#include "pop_back.hpp"
#include "pop_front.hpp"
#include "push_back.hpp"
#include "push_front.hpp"
#include "remove.hpp"
#include "remove_if.hpp"
#include "repeat.hpp"
#include "replace.hpp"
#include "replace_if.hpp"
#include "reverse.hpp"
#include "rotate.hpp"
#include "rotate_left.hpp"
#include "rotate_right.hpp"
#include "sort.hpp"
#include "take.hpp"
#include "take_back.hpp"
#include "take_front.hpp"
#include "transform.hpp"
#include "unique.hpp"
#include "unpack.hpp"
#include "zip.hpp"

// FIXME
// tests for common/helpers + split common helpers
// create a functional directory for functional helpers (curry/partial) + tests
// test for accumulate
// test for all
// test for all_of
// test for any
// test for any_of
// test for at
// test for contains
// test for copy
// test for count
// test for end
// test for find
// test for find_if
// test for helpers
// test for length
// test for nonte
// test for none_of
// test for remove
// test for repeat
// test for replace
// test for replace_if
// test for take
// test for take_back
// test for take_front
// test for transform
// test for unpack

// TODO
// at_key
// insert
// transpose
// mismatch
// curry / partial
// find_if_not / find_end / find_first_of
// adjacent_find
// search / search_n
// max / min / minmax
// max_el / min_el / minmax_el
// take_while
// fill / expand_with
// zip / zip_with / zip_shortest / zip_longest
// ap / lift
// cartesian_product
// permutation / partition
// empty / is_empty
// adjust / adjust_if
// yield / yield_n
// iota
// swap_at / swap_ranges_at
// shuffle (with compile_time rng from cpp-weakly's Jason Turner)
// lower_bound / upper_bound
// is_sorted / is_sorted_until
// sort_range / sort_until / nth_element
// includes
// set_difference / set_symmetric_difference
// set_intersection / set_union
// is_permutation / next_permutation / prev_permutation
// literals :
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/bool.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/fwd/integral_constant.hpp
// operators :
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/arithmetic.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/comparable.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/iterable.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/logical.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/monad.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/orderable.hpp
//    https://github.com/boostorg/hana/blob/master/include/boost/hana/detail/operators/searchable.hpp
// logical eval_if (lazy) / if_ / and_ / or_ / not_ / while_

// TODO
// pure type :
// all / all_of
// any / any_of
// none / none_of
// count / count_if
// at
// front / back
// pop_front / pop_back
// push_front / push_back
// find / find_if
// replace / replace_if
// copy / copy_if
// remove / remove_if
// reverse / rotate / rotate_left / rotate_right
// take / take_left / take_right
// fold / fold_left / fold_right
// sort
// transform
// unique
// cat
// insert
// cartesian_product
// transpose
// empty / is_empty
// fill / expand_with
// zip / zip_with / zip_shortest / zip_longest
// accumulate
// defer (lazy)
