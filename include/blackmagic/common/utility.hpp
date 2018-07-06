#pragma once

#include <cstddef>
#include <type_traits>

namespace blackmagic::common { inline namespace utility {

// all_of_v
struct all_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return (bools && ...);
  }
};

inline constexpr const all_of_v_t all_of_v{};


// any_of_v
struct any_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return (bools || ...);
  }
};

inline constexpr const any_of_v_t any_of_v{};


// none_of_v
struct none_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return !all_of_v(bools...);
  }
};

inline constexpr const none_of_v_t none_of_v{};


// count_v
struct count_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... nbs) const
  {
    static_assert((std::is_convertible_v<Ts, size_t> && ...), "Arguments not convertible to size_t.");
    return (nbs + ...);
  }
};

inline constexpr const count_v_t count_v{};


// are_equal
struct are_equal_t {
  template <typename T, typename... Ts>
  constexpr bool operator()(T&& lhs, Ts&&... rhs) const
  {
    return ((lhs == rhs) && ...);
  }
};

inline constexpr const are_equal_t are_equal{};


// are_not_equal
struct are_not_equal_t {
  template <typename T, typename... Ts>
  constexpr bool operator()(T&& lhs, Ts&&... rhs) const
  {
    return ((lhs != rhs) && ...);
  }
};

inline constexpr const are_not_equal_t are_not_equal{};

}} // namespace blackmagic::common::utility
