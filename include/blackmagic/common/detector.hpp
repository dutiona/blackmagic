#pragma once

#include "traits_ext.hpp"

#include "../type/list.hpp"

#include <type_traits>

namespace blackmagic::common { inline namespace detector {

// nonesuch
struct nonesuch {
  nonesuch()                = delete;
  ~nonesuch()               = delete;
  nonesuch(const nonesuch&) = delete;
  void operator=(const nonesuch&) = delete;
};


// is_detected
namespace {

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
using is_detected = typename detector<nonesuch, Op, type::basic_list<Args...>>::value_t;

template <template <typename...> class Op, typename... Args>
using detected_t = _t<detector<nonesuch, Op, type::basic_list<Args...>>>;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or = detector<Default, Op, type::basic_list<Args...>>;

template <template <typename...> class Op, typename... Args>
constexpr bool is_detected_v = _v<is_detected<Op, Args...>>;

template <typename Default, template <typename...> class Op, typename... Args>
using detected_or_t = _t<detected_or<Default, Op, Args...>>;

template <typename Expected, template <typename...> class Op, typename... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template <typename Expected, template <typename...> class Op, typename... Args>
constexpr bool is_detected_exact_v = _v<is_detected_exact<Expected, Op, Args...>>;

template <typename To, template <typename...> class Op, typename... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

template <typename To, template <typename...> class Op, typename... Args>
constexpr bool is_detected_convertible_v = _v<is_detected_convertible<To, Op, Args...>>;

}} // namespace blackmagic::common::test
