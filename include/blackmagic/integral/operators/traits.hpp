#pragma once

#include "../types.hpp"
#include "tag_of.hpp"

#include "../../common/traits_ext.hpp"

namespace blackmagic::integral { inline namespace operators { namespace trait {

namespace common = blackmagic::common;
using common::_t;

template <bool Status, typename T, typename U = T>
struct logical_trait {
  static constexpr auto logical_and = Status; // &&
  static constexpr auto logical_or  = Status; // ||
  static constexpr auto logical_not = Status; // !
};

template <bool Status, typename T, typename U = T>
struct comparison_trait {
  static constexpr auto equal_to           = Status; // ==
  static constexpr auto not_equal_to       = Status; // !=
  static constexpr auto less_than          = Status; // <
  static constexpr auto less_equal_than    = Status; // <=
  static constexpr auto greater_than       = Status; // >
  static constexpr auto greater_equal_than = Status; // >=
};

template <bool Status, typename T, typename U = T>
struct arithmetic_trait {
  static constexpr auto positive   = Status; // unary +
  static constexpr auto negative   = Status; // unary -
  static constexpr auto plus       = Status; // binary +
  static constexpr auto minus      = Status; // binary -
  static constexpr auto div        = Status; // /
  static constexpr auto mult       = Status; // *
  static constexpr auto mod        = Status; // %
  static constexpr auto bit_not    = Status; // ~
  static constexpr auto bit_and    = Status; // &
  static constexpr auto bit_or     = Status; // |
  static constexpr auto bit_xor    = Status; // ^
  static constexpr auto bit_lshift = Status; // <<
  static constexpr auto bit_rshift = Status; // >>
};


template <typename T>
struct enable_trait {
  static constexpr auto logical    = false;
  static constexpr auto comparison = false;
  static constexpr auto arithmetic = false;
};

template <>
struct enable_trait<_t<tag_of<bool_t>>> {
  static constexpr auto logical    = true;
  static constexpr auto comparison = false;
  static constexpr auto arithmetic = false;
};

template <>
struct enable_trait<_t<tag_of<char_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<short_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<int_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<long_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<long_long_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<unsigned_char_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<unsigned_short_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<unsigned_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<unsigned_long_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

template <>
struct enable_trait<_t<tag_of<unsigned_long_long_t>>> {
  static constexpr auto logical    = false;
  static constexpr auto comparison = true;
  static constexpr auto arithmetic = true;
};

}}} // namespace blackmagic::integral::operators::trait
