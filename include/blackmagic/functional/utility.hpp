#pragma once

#include <utility>

namespace blackmagic::functional { inline namespace utility { inline namespace functors {

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

struct plus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) + std::forward<U>(b);
  }
};
inline constexpr const plus_t plus{};

struct minus_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) - std::forward<U>(b);
  }
};
inline constexpr const minus_t minus{};

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

struct positive_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return +std::forward<T>(a);
  }
};
inline constexpr const positive_t positive{};

struct negative_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return -std::forward<T>(a);
  }
};
inline constexpr const negative_t negative{};

struct bit_not_t {
  template <typename T>
  constexpr decltype(auto) operator()(T&& a) const
  {
    return ~std::forward<T>(a);
  }
};
inline constexpr const bit_not_t bit_not{};

struct bit_and_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) & std::forward<U>(b);
  }
};
inline constexpr const bit_and_t bit_and{};

struct bit_or_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) | std::forward<U>(b);
  }
};
inline constexpr const bit_or_t bit_or{};

struct bit_xor_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) ^ std::forward<U>(b);
  }
};
inline constexpr const bit_xor_t bit_xor{};

struct bit_lshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) << std::forward<U>(b);
  }
};
inline constexpr const bit_lshift_t bit_lshift{};

struct bit_rshift_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) >> std::forward<U>(b);
  }
};
inline constexpr const bit_rshift_t bit_rshift{};


inline namespace assignement {
struct assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) = std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const assign_t assign{};

struct plus_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) += std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const plus_assign_t plus_assign{};

struct minus_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) -= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const minus_assign_t minus_assign{};

struct mult_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) *= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const mult_assign_t mult_assign{};

struct div_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) /= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const div_assign_t div_assign{};

struct mod_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) %= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const mod_assign_t mod_assign{};

struct bit_and_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) &= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const bit_and_assign_t bit_and_assign{};

struct bit_or_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) |= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const bit_or_assign_t bit_or_assign{};

struct bit_xor_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) ^= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const bit_xor_assign_t bit_xor_assign{};

struct bit_lshift_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) <<= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const bit_lshift_assign_t bit_lshift_assign{};

struct bit_rshift_assign_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    std::forward<T>(a) >>= std::forward<U>(b);
    return std::forward<T>(a);
  }
};
inline constexpr const bit_rshift_assign_t bit_rshift_assign{};

} // namespace assignement

} // namespace arithmetic


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

struct less_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) < std::forward<U>(b);
  }
};
inline constexpr const less_t less{};

struct less_equal_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) <= std::forward<U>(b);
  }
};
inline constexpr const less_equal_t less_equal{};

struct greater_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) > std::forward<U>(b);
  }
};
inline constexpr const greater_t greater{};

struct greater_equal_t {
  template <typename T, typename U>
  constexpr decltype(auto) operator()(T&& a, U&& b) const
  {
    return std::forward<T>(a) >= std::forward<U>(b);
  }
};
inline constexpr const greater_equal_t greater_equal{};

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
