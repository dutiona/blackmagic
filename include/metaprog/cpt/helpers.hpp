#pragma once

#ifndef METAPROG_CPT_HELPERS_HPP_
#define METAPROG_CPT_HELPERS_HPP_

#include <functional>
#include <type_traits>

namespace cpt { namespace helpers {

// nonesuch

struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};


// is_detected

namespace details {
template <typename Default, typename AlwaysVoid, template <typename...> class Op, typename... Args>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <typename Default, template <typename...> class Op, typename... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
  // Note that std::void_t is a C++17 feature
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <typename...> class Op, typename... Args>
using is_detected = typename details::detector<nonesuch, void, Op, Args...>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = typename details::detector<nonesuch, void, Op, Args...>::type;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = details::detector<Default, void, Op, Args...>;

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


// invoke_result

namespace details {

template <typename AlwaysVoid, typename, typename...>
struct invoke_result {
};
template <typename F, typename... Args>
struct invoke_result<decltype(void(std::invoke(std::declval<F>(), std::declval<Args>()...))), F, Args...> {
  using type = decltype(std::invoke(std::declval<F>(), std::declval<Args>()...));
};

} // namespace details

template <typename F, typename... Args>
struct invoke_result : details::invoke_result<void, F, Args...> {
};
template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;


// dependent false
template <typename... Args>
struct dependent_false : std::false_type {
  constexpr operator bool()
  {
    return std::false_type::value;
  }
};
template <typename... Args>
constexpr bool dependent_false_v = static_cast<bool>(dependent_false<Args...>{});

}} // namespace cpt::helpers

#endif // METAPROG_CPT_CONCEPTS_HELPERS_HPP_
