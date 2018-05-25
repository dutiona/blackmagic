#include <blackmagic/functional/functional.hpp>
#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace integral   = blackmagic::integral;

TEST(Functional_Iterate, Five)
{
  ASSERT_TRUE(functional::iterate([](auto n) { return n + 1; }, integral::size_t_t<5>{})(1) == 6);
}
