#include "../../../include/metaprog/cpt/cpt.hpp"

#include <gtest/gtest.h>

namespace concepts = cpt::concepts;

struct default_constructible_test {
};
struct not_default_constructible_test {
  not_default_constructible_test() = delete;
};

TEST(Cpt_Basic, default_constructible)
{
  using namespace ctx::literals;
  constexpr auto cpt_item  = cpt::make_concept_item<concepts::default_constructible>("test1"_s);
  constexpr auto cpt_item2 = cpt::make_concept_item<concepts::default_constructible>("test2"_s);
  constexpr auto cpt_map   = cpt::make_concept_map(cpt_item, cpt_item2);
  cpt::require_map<default_constructible_test>(cpt_map);
  cpt::require_map_at<default_constructible_test>(cpt_map, "test2"_s);
  [[maybe_unused]] constexpr bool ret  = cpt::check_map<default_constructible_test>(cpt_map);
  [[maybe_unused]] constexpr bool ret2 = cpt::check_map_at<default_constructible_test>(cpt_map, "test2"_s);

  ASSERT_TRUE((cpt::check<concepts::default_constructible, default_constructible_test>()));
  ASSERT_FALSE((cpt::check<concepts::default_constructible, not_default_constructible_test>()));
}

struct copy_constructible_test {
  copy_constructible_test()                               = delete;
  copy_constructible_test(const copy_constructible_test&) = default;
};
struct not_copy_constructible_test {
  not_copy_constructible_test()                                   = delete;
  not_copy_constructible_test(const not_copy_constructible_test&) = delete;
};

TEST(Cpt_Basic, copy_constructible)
{
  ASSERT_TRUE((cpt::check<concepts::copy_constructible, default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::copy_constructible, not_default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::copy_constructible, copy_constructible_test>()));
  ASSERT_FALSE((cpt::check<concepts::copy_constructible, not_copy_constructible_test>()));
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

TEST(Cpt_Basic, move_constructible)
{
  ASSERT_TRUE((cpt::check<concepts::move_constructible, default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_constructible, not_default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_constructible, copy_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_constructible, move_constructible_test>()));
  ASSERT_FALSE((cpt::check<concepts::move_constructible, not_copy_constructible_test>()));
  ASSERT_FALSE((cpt::check<concepts::move_constructible, not_move_constructible_test>()));
}

struct copy_assignable_test {
  copy_assignable_test()        = delete;
  copy_assignable_test& operator=(const copy_assignable_test&) = default;
};
struct not_copy_assignable_test {
  not_copy_assignable_test()        = delete;
  not_copy_assignable_test& operator=(const not_copy_assignable_test&) = delete;
};

TEST(Cpt_Basic, copy_assignable)
{
  ASSERT_TRUE((cpt::check<concepts::copy_assignable, default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::copy_assignable, not_default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::copy_assignable, copy_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::copy_assignable, not_copy_assignable_test>()));
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

TEST(Cpt_Basic, move_assignable)
{
  ASSERT_TRUE((cpt::check<concepts::move_assignable, default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_assignable, not_default_constructible_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_assignable, copy_assignable_test>()));
  ASSERT_TRUE((cpt::check<concepts::move_assignable, move_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::move_assignable, not_copy_assignable_test>()));
  ASSERT_FALSE((cpt::check<concepts::move_assignable, not_move_assignable_test>()));
}

struct destructible_test {
};
struct not_destructible_test {
  ~not_destructible_test() = delete;
};

TEST(Cpt_Basic, destructible)
{
  ASSERT_TRUE((cpt::check<concepts::destructible, destructible_test>()));
  ASSERT_FALSE((cpt::check<concepts::destructible, not_destructible_test>()));
}
