#pragma once

namespace blackmagic::integral { inline namespace tags {

template <template <auto...> class T>
struct tag_of;

template <>
struct tag_of<integral::bool_t> {
  using type = struct BoolTag;
};

template <>
struct tag_of<integral::char_t> {
  using type = struct CharTag;
};

template <>
struct tag_of<integral::short_t> {
  using type = struct ShortTag;
};

template <>
struct tag_of<integral::int_t> {
  using type = struct IntTag;
};

template <>
struct tag_of<integral::long_t> {
  using type = struct LongTag;
};

template <>
struct tag_of<integral::long_long_t> {
  using type = struct LongLongTag;
};

template <>
struct tag_of<integral::unsigned_char_t> {
  using type = struct UnsignedCharTag;
};

template <>
struct tag_of<integral::unsigned_short_t> {
  using type = struct UnsignedShortTag;
};

template <>
struct tag_of<integral::unsigned_t> {
  using type = struct UnsignedTag;
};

template <>
struct tag_of<integral::unsigned_int_t> {
  using type = struct UnsignedIntTag;
};

template <>
struct tag_of<integral::unsigned_long_t> {
  using type = struct UnsignedLong;
};

template <>
struct tag_of<integral::unsigned_long_long_t> {
  using type = struct UnsignedLongLongTag;
};

template <>
struct tag_of<integral::size_t_t> {
  using type = struct SizeTTag;
};

}} // namespace blackmagic::integral::tags
