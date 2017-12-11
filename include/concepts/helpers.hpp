#pragma once

#ifndef CONCEPTS_HELPERS_HPP_
#define CONCEPTS_HELPERS_HPP_

#include <functional>
#include <type_traits>
#include <utility>

namespace concepts { namespace helpers {

// nonesuch

struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};


// is_detected

namespace details {
template <class Default, class AlwaysVoid, template <class...> class Op, class... Args>
struct detector {
  using value_t = std::false_type;
  using type    = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
  // Note that std::void_t is a C++17 feature
  using value_t = std::true_type;
  using type    = Op<Args...>;
};

} // namespace details

template <template <class...> class Op, class... Args>
using is_detected = typename details::detector<nonesuch, void, Op, Args...>::value_t;

template <template <class...> class Op, class... Args>
using detected_t = typename details::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template <class...> class Op, class... Args>
using detected_or = details::detector<Default, void, Op, Args...>;

template <template <class...> class Op, class... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template <class Default, template <class...> class Op, class... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

template <class Expected, template <class...> class Op, class... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <class Expected, template <class...> class Op, class... Args>
constexpr bool is_detected_exact_v = is_detected_exact<Expected, Op, Args...>::value;

template <class To, template <class...> class Op, class... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template <class To, template <class...> class Op, class... Args>
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

}} // namespace concepts::helpers

#endif // CONCEPTS_HELPERS_HPP_
