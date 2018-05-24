#include <blackmagic/common/common.hpp>
#include <blackmagic/functional/functional.hpp>
#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace integral   = blackmagic::integral;
namespace common     = blackmagic::common;
using namespace integral::literals;
using namespace functional::placeholder;

TEST(Functional_While, Runtime)
{
  ASSERT_TRUE(functional::While((_ < 10), 0, [](auto a) { return a + 1; }) == 10);
}

using namespace blackmagic::integral::operators;

TEST(Functional_While, Compiletime)
{
  ASSERT_TRUE(functional::While(integral::less.than(10_c), 0_c,
                                [](auto&& a) { return blackmagic::integral::plus(std::forward<decltype(a)>(a), 1_c); })
              == 10_c);
}
