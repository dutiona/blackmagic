#pragma once

#ifndef CONCEPTS_BASIC_TRAITS_HPP_
#define CONCEPTS_BASIC_TRAITS_HPP_

#include <type_traits>

namespace traits { namespace basic {

// default constructible
using std::is_default_constructible;
using std::is_default_constructible_v;
template <typename T>
using is_default_constructible_t = typename std::is_default_constructible<T>::type;

using std::is_nothrow_default_constructible;
using std::is_nothrow_default_constructible_v;
template <typename T>
using is_nothrow_default_constructible_t = typename std::is_nothrow_default_constructible<T>::type;

using std::is_trivially_default_constructible;
using std::is_trivially_default_constructible_v;
template <typename T>
using is_trivially_default_constructible_t = typename std::is_trivially_default_constructible<T>::type;

// move constructible
using std::is_move_constructible;
using std::is_move_constructible_v;
template <typename T>
using is_move_constructible_t = typename std::is_move_constructible<T>::type;

using std::is_nothrow_move_constructible;
using std::is_nothrow_move_constructible_v;
template <typename T>
using is_nothrow_move_constructible_t = typename std::is_nothrow_move_constructible<T>::type;

using std::is_trivially_move_constructible;
using std::is_trivially_move_constructible_v;
template <typename T>
using is_trivially_move_constructible_t = typename std::is_trivially_move_constructible<T>::type;

// move assignable
using std::is_move_assignable;
using std::is_move_assignable_v;
template <typename T>
using is_move_assignable_t = typename std::is_move_assignable<T>::type;

using std::is_nothrow_move_assignable;
using std::is_nothrow_move_assignable_v;
template <typename T>
using is_nothrow_move_assignable_t = typename std::is_nothrow_move_assignable<T>::type;

using std::is_trivially_move_assignable;
using std::is_trivially_move_assignable_v;
template <typename T>
using is_trivially_move_assignable_t = typename std::is_trivially_move_assignable<T>::type;

// copy constructible
using std::is_copy_constructible;
using std::is_copy_constructible_v;
template <typename T>
using is_copy_constructible_t = typename std::is_copy_constructible<T>::type;

using std::is_nothrow_copy_constructible;
using std::is_nothrow_copy_constructible_v;
template <typename T>
using is_nothrow_copy_constructible_t = typename std::is_nothrow_copy_constructible<T>::type;

using std::is_trivially_copy_constructible;
using std::is_trivially_copy_constructible_v;
template <typename T>
using is_trivially_copy_constructible_t = typename std::is_trivially_copy_constructible<T>::type;

// copy assignable
using std::is_copy_assignable;
using std::is_copy_assignable_v;
template <typename T>
using is_copy_assignable_t = typename std::is_copy_assignable<T>::type;

using std::is_nothrow_copy_assignable;
using std::is_nothrow_copy_assignable_v;
template <typename T>
using is_nothrow_copy_assignable_t = typename std::is_nothrow_copy_assignable<T>::type;

using std::is_trivially_copy_assignable;
using std::is_trivially_copy_assignable_v;
template <typename T>
using is_trivially_copy_assignable_t = typename std::is_trivially_copy_assignable<T>::type;

// destructible
using std::is_destructible;
using std::is_destructible_v;
template <typename T>
using is_destructible_t = typename std::is_destructible<T>::type;

using std::is_nothrow_destructible;
using std::is_nothrow_destructible_v;
template <typename T>
using is_nothrow_destructible_t = typename std::is_nothrow_destructible<T>::type;

using std::is_trivially_destructible;
using std::is_trivially_destructible_v;
template <typename T>
using is_trivially_destructible_t = typename std::is_trivially_destructible<T>::type;

}} // namespace traits::basic

#endif // CONCEPTS_BASIC_TRAITS_HPP_
