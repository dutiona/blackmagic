#pragma once

#include "../../common/traits_ext.hpp"

#include <type_traits>

namespace blackmagic::traits { inline namespace basic {

using blackmagic::common::_t;

// default constructible
using std::is_default_constructible;
using std::is_default_constructible_v;
template <typename T>
using is_default_constructible_t = _t<is_default_constructible<T>>;

using std::is_nothrow_default_constructible;
using std::is_nothrow_default_constructible_v;
template <typename T>
using is_nothrow_default_constructible_t = _t<is_nothrow_default_constructible<T>>;

using std::is_trivially_default_constructible;
using std::is_trivially_default_constructible_v;
template <typename T>
using is_trivially_default_constructible_t = _t<is_trivially_default_constructible<T>>;

// move constructible
using std::is_move_constructible;
using std::is_move_constructible_v;
template <typename T>
using is_move_constructible_t = _t<is_move_constructible<T>>;

using std::is_nothrow_move_constructible;
using std::is_nothrow_move_constructible_v;
template <typename T>
using is_nothrow_move_constructible_t = _t<is_nothrow_move_constructible<T>>;

using std::is_trivially_move_constructible;
using std::is_trivially_move_constructible_v;
template <typename T>
using is_trivially_move_constructible_t = _t<is_trivially_move_constructible<T>>;

// move assignable
using std::is_move_assignable;
using std::is_move_assignable_v;
template <typename T>
using is_move_assignable_t = _t<is_move_assignable<T>>;

using std::is_nothrow_move_assignable;
using std::is_nothrow_move_assignable_v;
template <typename T>
using is_nothrow_move_assignable_t = _t<is_nothrow_move_assignable<T>>;

using std::is_trivially_move_assignable;
using std::is_trivially_move_assignable_v;
template <typename T>
using is_trivially_move_assignable_t = _t<is_trivially_move_assignable<T>>;

// copy constructible
using std::is_copy_constructible;
using std::is_copy_constructible_v;
template <typename T>
using is_copy_constructible_t = _t<is_copy_constructible<T>>;

using std::is_nothrow_copy_constructible;
using std::is_nothrow_copy_constructible_v;
template <typename T>
using is_nothrow_copy_constructible_t = _t<is_nothrow_copy_constructible<T>>;

using std::is_trivially_copy_constructible;
using std::is_trivially_copy_constructible_v;
template <typename T>
using is_trivially_copy_constructible_t = _t<is_trivially_copy_constructible<T>>;

// copy assignable
using std::is_copy_assignable;
using std::is_copy_assignable_v;
template <typename T>
using is_copy_assignable_t = _t<is_copy_assignable<T>>;

using std::is_nothrow_copy_assignable;
using std::is_nothrow_copy_assignable_v;
template <typename T>
using is_nothrow_copy_assignable_t = _t<is_nothrow_copy_assignable<T>>;

using std::is_trivially_copy_assignable;
using std::is_trivially_copy_assignable_v;
template <typename T>
using is_trivially_copy_assignable_t = _t<is_trivially_copy_assignable<T>>;

// destructible
using std::is_destructible;
using std::is_destructible_v;
template <typename T>
using is_destructible_t = _t<is_destructible<T>>;

using std::is_nothrow_destructible;
using std::is_nothrow_destructible_v;
template <typename T>
using is_nothrow_destructible_t = _t<is_nothrow_destructible<T>>;

using std::is_trivially_destructible;
using std::is_trivially_destructible_v;
template <typename T>
using is_trivially_destructible_t = _t<is_trivially_destructible<T>>;

}} // namespace blackmagic::traits::basic
