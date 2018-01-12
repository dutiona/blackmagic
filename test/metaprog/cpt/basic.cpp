#include <metaprog/cpt/cpt.hpp>

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

struct default_constructible_test {
};

struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

TEST(Cpt_Basic, DefaultConstructible)
{
  ASSERT_TRUE((concepts::DefaultConstructible.check<default_constructible_test>()));
  ASSERT_FALSE((concepts::DefaultConstructible.check<not_default_constructible_test>()));
}

struct copy_constructible_test {
  copy_constructible_test()                               = delete;
  copy_constructible_test(const copy_constructible_test&) = default;
};

struct not_copy_constructible_test {
  not_copy_constructible_test()                                   = delete;
  not_copy_constructible_test(const not_copy_constructible_test&) = delete;
};

TEST(Cpt_Basic, CopyConstructible)
{
  ASSERT_TRUE((concepts::CopyConstructible.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::CopyConstructible.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::CopyConstructible.check<copy_constructible_test>()));
  ASSERT_FALSE((concepts::CopyConstructible.check<not_copy_constructible_test>()));
}

struct move_constructible_test {
  move_constructible_test()                               = delete;
  move_constructible_test(const move_constructible_test&) = delete;
  move_constructible_test(move_constructible_test&&)      = default;
};

struct not_move_constructible_test {
  not_move_constructible_test()                                   = delete;
  not_move_constructible_test(const not_move_constructible_test&) = delete;
  not_move_constructible_test(not_move_constructible_test&&)      = delete;
};

TEST(Cpt_Basic, MoveConstructible)
{
  ASSERT_TRUE((concepts::MoveConstructible.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::MoveConstructible.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::MoveConstructible.check<copy_constructible_test>()));
  ASSERT_TRUE((concepts::MoveConstructible.check<move_constructible_test>()));
  ASSERT_FALSE((concepts::MoveConstructible.check<not_copy_constructible_test>()));
  ASSERT_FALSE((concepts::MoveConstructible.check<not_move_constructible_test>()));
}

struct copy_assignable_test {
  copy_assignable_test() = delete;

  copy_assignable_test& operator=(const copy_assignable_test&) = default;
};

struct not_copy_assignable_test {
  not_copy_assignable_test()        = delete;
  not_copy_assignable_test& operator=(const not_copy_assignable_test&) = delete;
};

TEST(Cpt_Basic, CopyAssignable)
{
  ASSERT_TRUE((concepts::CopyAssignable.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::CopyAssignable.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::CopyAssignable.check<copy_assignable_test>()));
  ASSERT_FALSE((concepts::CopyAssignable.check<not_copy_assignable_test>()));
}

struct move_assignable_test {
  move_assignable_test()        = delete;
  move_assignable_test& operator=(const copy_assignable_test&) = delete;
  move_assignable_test& operator=(move_assignable_test&&) = default;
};

struct not_move_assignable_test {
  not_move_assignable_test()        = delete;
  not_move_assignable_test& operator=(const not_move_assignable_test&) = delete;
  not_move_assignable_test& operator=(not_move_assignable_test&&) = delete;
};

TEST(Cpt_Basic, MoveAssignable)
{
  ASSERT_TRUE((concepts::MoveAssignable.check<default_constructible_test>()));
  ASSERT_TRUE((concepts::MoveAssignable.check<not_default_constructible_test>()));
  ASSERT_TRUE((concepts::MoveAssignable.check<copy_assignable_test>()));
  ASSERT_TRUE((concepts::MoveAssignable.check<move_assignable_test>()));
  ASSERT_FALSE((concepts::MoveAssignable.check<not_copy_assignable_test>()));
  ASSERT_FALSE((concepts::MoveAssignable.check<not_move_assignable_test>()));
}

struct destructible_test {
};

struct not_destructible_test {
  ~not_destructible_test() = delete;
};

TEST(Cpt_Basic, destructible)
{
  ASSERT_TRUE((concepts::Destructible.check<destructible_test>()));
  ASSERT_FALSE((concepts::Destructible.check<not_destructible_test>()));
}
