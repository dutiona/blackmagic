#include <gtest/gtest.h>

#include "../../../include/metaprog/ctx/ctx.hpp"

#include <string_view>

using namespace ctx::literals;

TEST(Ctx_Map, basic_indexing)
{
  ctx::map<ctx::string, bool> m;
  m["test"_s] = true;
  ASSERT_TRUE(m.at("test"_s));
}
