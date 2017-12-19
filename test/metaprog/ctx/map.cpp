#include <metaprog/ctx/ctx.hpp>

#include <string_view>

#include <gtest/gtest.h>

using namespace std::literals;

TEST(Ctx_Map, basic_indexing)
{
  ctx::map<std::string_view, bool> m;
  m["test"sv] = true;
  ASSERT_TRUE(m.at("test"sv));
}
