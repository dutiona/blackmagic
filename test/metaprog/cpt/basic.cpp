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
  ASSERT_TRUE((concepts::default_constructible.check<default_constructible_test>()));
  ASSERT_FALSE((concepts::default_constructible.check<not_default_constructible_test>()));
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
  ASSERT_TRUE((concepts::copy_constructible.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::copy_constructible.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::copy_constructible.check<copy_constructible_test>()));
  ASSERT_FALSE((concepts::copy_constructible.check<not_copy_constructible_test>()));
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
  ASSERT_TRUE((concepts::move_constructible.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::move_constructible.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::move_constructible.check<copy_constructible_test>()));
  ASSERT_TRUE((concepts::move_constructible.check<move_constructible_test>()));
  ASSERT_FALSE((concepts::move_constructible.check<not_copy_constructible_test>()));
  ASSERT_FALSE((concepts::move_constructible.check<not_move_constructible_test>()));
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
  ASSERT_TRUE((concepts::copy_assignable.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::copy_assignable.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::copy_assignable.check<copy_assignable_test>()));
  ASSERT_FALSE((concepts::copy_assignable.check<not_copy_assignable_test>()));
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
  ASSERT_TRUE((concepts::move_assignable.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::move_assignable.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::move_assignable.check<copy_assignable_test>()));
  ASSERT_TRUE((concepts::move_assignable.check<move_assignable_test>()));
  ASSERT_FALSE((concepts::move_assignable.check<not_copy_assignable_test>()));
  ASSERT_FALSE((concepts::move_assignable.check<not_move_assignable_test>()));
}

struct destructible_test {
};

struct not_destructible_test {
  ~not_destructible_test() = delete;
};

TEST(Cpt_Basic, destructible)
{
  ASSERT_TRUE((concepts::destructible.check<destructible_test>()));
  ASSERT_FALSE((concepts::destructible.check<not_destructible_test>()));
}
