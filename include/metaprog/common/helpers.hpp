#pragma once

#include <metaprog/type/type.hpp>

#ifdef __GLIBCXX__
#include "../cstxpr/cstxpr.hpp"
#endif // __GLIBCXX__

#include <functional>
#include <string_view>
#include <type_traits>

namespace metaprog::common::helpers {

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
  constexpr operator bool()
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


// all_of / any_of / none_of / count cstxpr
template <typename... Ts>
constexpr bool all_of(Ts... bools)
{
  static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
  return (bools && ...);
}

template <typename... Ts>
constexpr bool any_of(Ts... bools)
{
  static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
  return (bools || ...);
}
template <typename... Ts>
constexpr bool none_of(Ts... bools)
{
  static_assert((std::is_convertible_v<Ts, bool> && ...), "Arguments not convertible to bool.");
  return !all_of(bools...);
}
template <typename... Ts>
constexpr size_t count(Ts... nbs)
{
  static_assert((std::is_convertible_v<Ts, size_t> && ...), "Arguments not convertible to size_t.");
  return (nbs + ...);
}

} // namespace metaprog::common::helpers
