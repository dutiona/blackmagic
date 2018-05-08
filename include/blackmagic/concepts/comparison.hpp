#pragma once

/*
////////////////////////////////////////////////////////////////////////////////////////////
// Comparison concepts
////////////////////////////////////////////////////////////////////////////////////////////
struct WeaklyEqualityComparable
{
  template<typename T, typename U>
  auto requires_(detail::as_cref_t<T> t, detail::as_cref_t<U> u) -> decltype(
  // Not to spec: doesn't compare to a Boolean trait
  concepts::valid_expr(
    concepts::convertible_to<bool>(t == u),
    concepts::convertible_to<bool>(t != u),
    concepts::convertible_to<bool>(u == t),
    concepts::convertible_to<bool>(u != t)
  ));
};

struct EqualityComparable
{
  template<typename T>
  auto requires_(detail::as_cref_t<T> t) -> decltype(
  concepts::valid_expr(
    concepts::convertible_to<bool>(t == t),
    concepts::convertible_to<bool>(t != t)
  ));

  template<typename T, typename U>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::is_true(std::is_same<T, U>{}),
    concepts::model_of<EqualityComparable, T>()
  ));

  // Cross-type equality comparison from N3351:
  // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3351.pdf
  template<typename T, typename U,
    typename C = common_reference_t<detail::as_cref_t<T>, detail::as_cref_t<U>>>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::is_false(std::is_same<T, U>{}),
    concepts::model_of<EqualityComparable, T>(),
    concepts::model_of<EqualityComparable, U>(),
    concepts::model_of<WeaklyEqualityComparable, T, U>(),
    concepts::model_of<
    CommonReference, detail::as_cref_t<T>, detail::as_cref_t<U>>(),
    concepts::model_of<EqualityComparable, C>()
  ));
};

struct WeaklyOrdered
{
  template<typename T>
  auto requires_(T && t) -> decltype(
  concepts::valid_expr(
    concepts::convertible_to<bool>(t < t),
    concepts::convertible_to<bool>(t > t),
    concepts::convertible_to<bool>(t <= t),
    concepts::convertible_to<bool>(t >= t)
  ));

  template<typename T, typename U,
    typename C = common_reference_t<detail::as_cref_t<T>, detail::as_cref_t<U>>>
  auto requires_(detail::as_cref_t<T> t, detail::as_cref_t<U> u) -> decltype(
  concepts::valid_expr(
    concepts::model_of<WeaklyOrdered, T>(),
    concepts::model_of<WeaklyOrdered, U>(),
    concepts::model_of<
    CommonReference, detail::as_cref_t<T>, detail::as_cref_t<U>>(),
    concepts::model_of<WeaklyOrdered, C>(),
    concepts::convertible_to<bool>(t < u),
    concepts::convertible_to<bool>(u < t),
    concepts::convertible_to<bool>(t > u),
    concepts::convertible_to<bool>(u > t),
    concepts::convertible_to<bool>(t <= u),
    concepts::convertible_to<bool>(u <= t),
    concepts::convertible_to<bool>(t >= u),
    concepts::convertible_to<bool>(u >= t)
  ));
};

struct TotallyOrdered
  : refines<EqualityComparable, WeaklyOrdered>
{
  template<typename T>
  void requires_();

  template<typename T, typename U>
  auto requires_() -> decltype(
  concepts::valid_expr(
    concepts::model_of<TotallyOrdered, T>(),
    concepts::model_of<TotallyOrdered, U>()
  ));
};
 */