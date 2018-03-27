#pragma once

#if __has_include(<optional>)
#include <optional>
namespace details {
using std::nullopt_t;
using std::optional;
} // namespace details
#else
#include <experimental/optional>
namespace details {
using std::experimental::nullopt_t;
using std::experimental::optional;
} // namespace details
#endif

namespace metaprog::cstxpr {

template <typename T>
struct optional {
  using value_type = T;

  constexpr optional(details::nullopt_t)
  {
  }

  constexpr explicit optional(const T& t)
    : m_valid(true)
    , m_t(t)
  {
  }

  constexpr explicit operator bool() const
  {
    return m_valid;
  }

  constexpr const T* operator->() const
  {
    return &m_t;
  }
  constexpr T* operator->()
  {
    return &m_t;
  }
  constexpr const T& operator*() const
  {
    return m_t;
  }
  constexpr T& operator*()
  {
    return m_t;
  }

private:
  bool m_valid = false;
  T    m_t{};
};

template <typename T>
constexpr auto make_optional(T&& t)
{
  return optional<T>(std::forward<T>(t));
}

} // namespace metaprog::cstxpr
