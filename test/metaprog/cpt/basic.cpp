#include <metaprog/cpt/cpt.hpp>

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

struct default_constructible_test {
};

struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

TEST(Cpt_Basic, default_constructible)
{
  ASSERT_TRUE((cpt::check<default_constructible_test>(concepts::default_constructible)));
  ASSERT_FALSE((cpt::check<not_default_constructible_test>(concepts::default_constructible)));
}

struct copy_constructible_test {
  copy_constructible_test() = delete;

  copy_constructible_test(const copy_constructible_test&) = default;
};

struct not_copy_constructible_test {
  not_copy_constructible_test() = delete;

  not_copy_constructible_test(const not_copy_constructible_test&) = delete;
};

TEST(Cpt_Basic, copy_constructible)
{
  ASSERT_TRUE((cpt::check<default_constructible_test>(concepts::copy_constructible)));
  ASSERT_TRUE((cpt::check<not_default_constructible_test>(concepts::copy_constructible)));
  ASSERT_TRUE((cpt::check<copy_constructible_test>(concepts::copy_constructible)));
  ASSERT_FALSE((cpt::check<not_copy_constructible_test>(concepts::copy_constructible)));
}

struct move_constructible_test {
  move_constructible_test() = delete;

  move_constructible_test(const move_constructible_test&) = delete;

  move_constructible_test(move_constructible_test&&) = default;
};

struct not_move_constructible_test {
  not_move_constructible_test() = delete;

  not_move_constructible_test(const not_move_constructible_test&) = delete;

  not_move_constructible_test(not_move_constructible_test&&) = delete;
};

TEST(Cpt_Basic, move_constructible)
{
  ASSERT_TRUE((cpt::check<default_constructible_test>(concepts::move_constructible)));
  ASSERT_TRUE((cpt::check<not_default_constructible_test>(concepts::move_constructible)));
  ASSERT_TRUE((cpt::check<copy_constructible_test>(concepts::move_constructible)));
  ASSERT_TRUE((cpt::check<move_constructible_test>(concepts::move_constructible)));
  ASSERT_FALSE((cpt::check<not_copy_constructible_test>(concepts::move_constructible)));
  ASSERT_FALSE((cpt::check<not_move_constructible_test>(concepts::move_constructible)));
}

struct copy_assignable_test {
  copy_assignable_test() = delete;

  copy_assignable_test& operator=(const copy_assignable_test&) = default;
};

struct not_copy_assignable_test {
  not_copy_assignable_test() = delete;

  not_copy_assignable_test& operator=(const not_copy_assignable_test&) = delete;
};

TEST(Cpt_Basic, copy_assignable)
{
  ASSERT_TRUE((cpt::check<default_constructible_test>(concepts::copy_assignable)));
  ASSERT_TRUE((cpt::check<not_default_constructible_test>(concepts::copy_assignable)));
  ASSERT_TRUE((cpt::check<copy_assignable_test>(concepts::copy_assignable)));
  ASSERT_FALSE((cpt::check<not_copy_assignable_test>(concepts::copy_assignable)));
}

struct move_assignable_test {
  move_assignable_test() = delete;

  move_assignable_test& operator=(const copy_assignable_test&) = delete;

  move_assignable_test& operator=(move_assignable_test&&) = default;
};

struct not_move_assignable_test {
  not_move_assignable_test() = delete;

  not_move_assignable_test& operator=(const not_move_assignable_test&) = delete;

  not_move_assignable_test& operator=(not_move_assignable_test&&) = delete;
};

TEST(Cpt_Basic, move_assignable)
{
  ASSERT_TRUE((cpt::check<default_constructible_test>(concepts::move_assignable)));
  ASSERT_TRUE((cpt::check<not_default_constructible_test>(concepts::move_assignable)));
  ASSERT_TRUE((cpt::check<copy_assignable_test>(concepts::move_assignable)));
  ASSERT_TRUE((cpt::check<move_assignable_test>(concepts::move_assignable)));
  ASSERT_FALSE((cpt::check<not_copy_assignable_test>(concepts::move_assignable)));
  ASSERT_FALSE((cpt::check<not_move_assignable_test>(concepts::move_assignable)));
}

struct destructible_test {
};

struct not_destructible_test {
  ~not_destructible_test() = delete;
};

TEST(Cpt_Basic, destructible)
{
  ASSERT_TRUE((cpt::check<destructible_test>(concepts::destructible)));
  ASSERT_FALSE((cpt::check<not_destructible_test>(concepts::destructible)));
}
