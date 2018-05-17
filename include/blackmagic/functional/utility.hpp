#pragma once

#include <utility>

namespace blackmagic::functional { inline namespace utility { inline namespace functors {
inline namespace arithmetic {
struct preincrement_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return ++std::forward<T>(a);
  }
};
inline constexpr const preincrement_t preincrement{};

struct postincrement_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return std::forward<T>(a)++;
  }
};
inline constexpr const postincrement_t postincrement{};

struct predecrement_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return --std::forward<T>(a);
  }
};
inline constexpr const predecrement_t predecrement{};

struct postdecrement_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return std::forward<T>(a)--;
  }
};
inline constexpr const postdecrement_t postdecrement{};

struct binary_plus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) + std::forward<U>(b);
  }
};
inline constexpr const binary_plus_t binary_plus{};

struct binary_minus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) - std::forward<U>(b);
  }
};
inline constexpr const binary_minus_t binary_minus{};

struct div_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) / std::forward<U>(b);
  }
};
inline constexpr const div_t div{};

struct mult_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) * std::forward<U>(b);
  }
};
inline constexpr const mult_t mult{};

struct mod_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) % std::forward<U>(b);
  }
};
inline constexpr const mod_t mod{};

struct unary_plus_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return +std::forward<T>(a);
  }
};
inline constexpr const unary_plus_t unary_plus{};

struct unary_minus_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return -std::forward<T>(a);
  }
};
inline constexpr const unary_minus_t unary_minus{};


inline namespace assignement {
struct assignable_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) = std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_t assignable{};

struct assignable_plus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) += std::forward<U>(b);
    return a;
  }
};
inline constexpr const assignable_plus_t assignable_plus{};

struct assignable_minus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) -= std::forward<U>(b);
    return a;
  }
};
inline constexpr const assignable_minus_t assignable_minus{};

struct assignable_mult_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) *= std::forward<U>(b);
    return a;
  }
};
inline constexpr const assignable_mult_t assignable_mult{};

struct assignable_div_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) /= std::forward<U>(b);
    return a;
  }
};
inline constexpr const assignable_div_t assignable_div{};

struct assignable_mod_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) %= std::forward<U>(b);
    return a;
  }
};
inline constexpr const assignable_mod_t assignable_mod{};

} // namespace assignement

} // namespace arithmetic


inline namespace bitwise {
struct not_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return ~std::forward<T>(a);
  }
};
inline constexpr const not_t Not{};

struct and_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) & std::forward<U>(b);
  }
};
inline constexpr const and_t And{};

struct or_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) | std::forward<U>(b);
  }
};
inline constexpr const or_t Or{};

struct xor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) ^ std::forward<U>(b);
  }
};
inline constexpr const xor_t Xor{};

struct lshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) << std::forward<U>(b);
  }
};
inline constexpr const lshift_t lshift{};

struct rshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) >> std::forward<U>(b);
  }
};
inline constexpr const rshift_t rshift{};


inline namespace assignement {
struct assignable_and_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) &= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_and_t assignable_and{};

struct assignable_or_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) |= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_or_t assignable_or{};

struct assignable_xor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) ^= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_xor_t assignable_xor{};

struct assignable_lshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) <<= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_lshift_t assignable_lshift{};

struct assignable_rshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) >>= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assignable_rshift_t assignable_rshift{};

} // namespace assignement

} // namespace bitwise

inline namespace comparison {
struct equal_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) == std::forward<U>(b);
  }
};
inline constexpr const equal_t equal{};

struct not_equal_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) != std::forward<U>(b);
  }
};
inline constexpr const not_equal_t not_equal{};

struct less_than_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) < std::forward<U>(b);
  }
};
inline constexpr const less_than_t less_than{};

struct less_equal_than_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) <= std::forward<U>(b);
  }
};
inline constexpr const less_equal_than_t less_equal_than{};

struct greater_than_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) > std::forward<U>(b);
  }
};
inline constexpr const greater_than_t greater_than{};

struct greater_equal_than_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) >= std::forward<U>(b);
  }
};
inline constexpr const greater_equal_than_t greater_equal_than{};

} // namespace comparison


inline namespace logical {
struct logical_and_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) && std::forward<U>(b);
  }
};
inline constexpr const logical_and_t logical_and{};

struct logical_or_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) || std::forward<U>(b);
  }
};
inline constexpr const logical_or_t logical_or{};

struct logical_not_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return !std::forward<T>(a);
  }
};
inline constexpr const logical_not_t logical_not{};

} // namespace logical


inline namespace member_access {
struct indirection_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return *std::forward<T>(a);
  }
};
inline constexpr const indirection_t indirection{};

struct address_of_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return &std::forward<T>(a);
  }
};
inline constexpr const address_of_t address_of{};

struct subscript_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& i) const
  {
    return std::forward<T>(a)[std::forward<U>(i)];
  }
};
inline constexpr const subscript_t subscript{};

} // namespace member_access


inline namespace other {
struct invocable_t {
  template <typename T, typename... Args>
  constexpr decltype(auto) operator()(T&& a, Args&&... args) const
  {
    return std::forward<T>(a)(std::forward<Args>(args)...);
  }
};
inline constexpr const invocable_t invocable{};

} // namespace other

}}} // namespace blackmagic::functional::utility::functors
