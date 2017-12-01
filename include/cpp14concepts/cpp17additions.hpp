#pragma once

#ifndef CPP14CONCEPTS_CPP17ADDITIONS_HPP_
#  define CPP14CONCEPTS_CPP17ADDITIONS_HPP_

#  include <type_traits>
#  include <utility>

namespace cpp14concepts { namespace cpp17additions {

// void_t

template <class...>
using void_t = void;


// nonesuch

struct nonesuch {
  nonesuch() = delete;
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};


// is_detected

namespace details {
template <class Default, class AlwaysVoid, template <class...> class Op, class... Args>
struct detector {
  using value_t = std::false_type;
  using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
  // Note that std::void_t is a C++17 feature
  using value_t = std::true_type;
  using type = Op<Args...>;
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


// is_referenceable

namespace details {

struct two {
  char lx[2];
};
struct is_referenceable_impl {
  template <class T>
  static T& test(int);

  template <class T>
  static two test(...);
};

} // namespace details

template <class T>
struct is_referenceable
  : std::integral_constant<bool,
                           !std::is_same<decltype(details::is_referenceable_impl::test<T>(0)), details::two>::value> {
};

// is_swappable

template <class T>
struct is_swappable;
template <class T>
struct is_nothrow_swappable;

namespace details {

using std::swap;

template <class T, class U = T, bool NotVoid = std::is_void<T>::value&& std::is_void<U>::value>
struct swappable_with {
  template <class Lhs, class Rhs>
  static decltype(swap(std::declval<Lhs>(), std::declval<Rhs>())) test_swap(int);
  template <class, class>
  static nonesuch test_swap(long);

  // Extra parens are needed for the C++03 definition of decltype.
  typedef decltype((test_swap<T, U>(0))) swap1;
  typedef decltype((test_swap<U, T>(0))) swap2;

  static const bool value = std::is_same<swap1, nonesuch>::value && !std::is_same<swap2, nonesuch>::value;
};

template <class T, class U>
struct swappable_with<T, U, false> : std::false_type {
};

template <class T, class U = T, bool = swappable_with<T, U>::value>
struct nothrow_swappable_with {
  static const bool value =
    noexcept(swap(std::declval<T>(), std::declval<U>())) && noexcept(swap(std::declval<U>(), std::declval<T>()));
};

template <class T, class U>
struct nothrow_swappable_with<T, U, false> : std::false_type {
};

template <class T>
struct is_swappable : public std::integral_constant<bool, swappable_with<T&>::value> {
};

template <class T>
struct is_nothrow_swappable : public std::integral_constant<bool, nothrow_swappable_with<T&>::value> {
};

} // namespace details


template <class T, class U>
struct is_swappable_with : public std::integral_constant<bool, details::swappable_with<T, U>::value> {
};

template <class T>
struct is_swappable
  : public std::conditional<
      is_referenceable<T>::value,
      is_swappable_with<typename std::add_lvalue_reference<T>::type, typename std::add_lvalue_reference<T>::type>,
      std::false_type>::type {
};

template <class T, class U>
struct is_nothrow_swappable_with : public std::integral_constant<bool, details::nothrow_swappable_with<T, U>::value> {
};

template <class T>
struct is_nothrow_swappable
  : public std::conditional<is_referenceable<T>::value,
                            is_nothrow_swappable_with<typename std::add_lvalue_reference<T>::type,
                                                      typename std::add_lvalue_reference<T>::type>,
                            std::false_type>::type {
};

template <class T, class U>
constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;

template <class T>
constexpr bool is_swappable_v = is_swappable<T>::value;

template <class T, class U>
constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;

template <class T>
constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

}} // namespace cpp14concepts::cpp17additions

#endif // CPP14CONCEPTS_CPP17ADDITIONS_HPP_
