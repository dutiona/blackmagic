#pragma once

#include "../type/type.hpp"

#ifdef __GLIBCXX__
#include "../cstxpr/cstxpr.hpp"
#endif // __GLIBCXX__

#include <functional>
#include <string_view>
#include <type_traits>

namespace metaprog::common::helpers {

// remove_cvref
template <typename T>
using remove_cvref = std::remove_cv<std::remove_reference_t<T>>;

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// nonesuch
struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(const nonesuch&) = delete;
  void operator=(const nonesuch&) = delete;
};


// is_detected
namespace details {

template <typename Default, template <typename...> class Op, typename ParametersPack, typename = void>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <typename Default, template <typename...> class Op, template <typename...> class ParametersPack,
          typename... Args>
struct detector<Default, Op, ParametersPack<Args...>, std::void_t<Op<Args...>>> {
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <typename...> class Op, typename... Args>
using is_detected = typename details::detector<nonesuch, Op, type::basic_list<Args...>>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = typename details::detector<nonesuch, Op, type::basic_list<Args...>>::type;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = details::detector<Default, Op, type::basic_list<Args...>>;

template <template <typename...> class Op, typename... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

template <typename Expected, template <typename...> class Op, typename... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <typename Expected, template <typename...> class Op, typename... Args>
constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

template <typename To, template <typename...> class Op, typename... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template <typename To, template <typename...> class Op, typename... Args>
constexpr bool is_detected_convertible_v = is_detected_convertible<To, Op, Args...>::value;


// dependent false
template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool() const
  {
    return value;
  }
};

template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});


// operator==(string_view, string_view) is not cstxpr yet in libstdc++
constexpr bool equals(std::string_view lhs, std::string_view rhs)
{
#ifdef __GLIBCXX__
  return cstxpr::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
#else
  return lhs == rhs;
#endif // __GLIBCXX__
}


// all_of
template <bool... Bs>
struct all_of : std::conjunction<std::bool_constant<Bs>...> {
};


// any_of
template <bool... Bs>
struct any_of : std::disjunction<std::bool_constant<Bs>...> {
};


// none_of
template <bool... Bs>
struct none_of : std::conjunction<std::bool_constant<!Bs>...> {
};


// count
template <bool... Bs>
struct count : std::integral_constant<size_t, (Bs + ...)> {
};

// all_of_v
namespace details {
struct all_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return (bools && ...);
  }
};
} // namespace details

inline constexpr details::all_of_v_t all_of_v{};


// any_of_v
namespace details {
struct any_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return (bools || ...);
  }
};
} // namespace details

inline constexpr details::any_of_v_t any_of_v{};


// none_of_v
namespace details {
struct none_of_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... bools) const
  {
    static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
    return !all_of_v(bools...);
  }
};
} // namespace details

inline constexpr details::none_of_v_t none_of_v{};


// count_v
namespace details {
struct count_v_t {
  template <typename... Ts>
  constexpr bool operator()(Ts... nbs) const
  {
    static_assert((std::is_convertible_v<Ts, size_t> && ...), "Arguments not convertible to size_t.");
    return (nbs + ...);
  }
};
} // namespace details

inline constexpr details::count_v_t count_v{};


// trait
template <template <typename...> class Pred, typename... Us>
struct trait_t {
  template <typename... Args>
  using type = typename Pred<Us..., Args...>::type;
  template <typename... Args>
  static constexpr auto value = Pred<Us..., Args...>::value;

  template <typename... Args>
  constexpr auto operator()(Us&&..., Args&&...) const
  {
    return value<Us..., Args...>;
  }
};

template <template <typename...> class Pred, typename... Us>
inline constexpr trait_t<Pred, Us...> trait{};

} // namespace metaprog::common::helpers
