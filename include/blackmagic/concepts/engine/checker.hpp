#pragma once

namespace blackmagic::concepts { inline namespace engine {

// Helper class storing a concept to perform a check later on
template <typename Concept>
struct checker {
  constexpr checker() = default;

  // force non failure at compile time when concept isn't verified
  template <typename... Args>
  constexpr bool check() const
  {
    return Concept::template value<Args...>;
  }

  template <auto... Args>
  constexpr bool check_v() const
  {
    return Concept::template value<Args...>;
  }

  // force fail at compile time when concept isn't verified
  template <typename... Args>
  constexpr void require() const
  {
    static_assert(Concept::template value<Args...>, "Concept assertion error");
  }

  template <auto... Args>
  constexpr void require_v() const
  {
    static_assert(Concept::template value<Args...>, "Concept assertion error");
  }
};

// Quick check/require a concept via helper function
template <typename Concept, typename... Args>
constexpr void require_concept()
{
  checker<Concept>{}.template require<Args...>();
}

template <typename Concept, auto... Args>
constexpr void require_v_concept()
{
  checker<Concept>{}.template require_v<Args...>();
}

template <typename Concept, typename... Args>
constexpr bool check_concept()
{
  return checker<Concept>{}.template check<Args...>();
}

template <typename Concept, auto... Args>
constexpr bool check_v_concept()
{
  return checker<Concept>{}.template check_v<Args...>();
}

}} // namespace blackmagic::concepts::engine
