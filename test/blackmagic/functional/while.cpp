#include <blackmagic/functional/functional.hpp>
#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace integral   = blackmagic::integral;
using namespace integral::literals;
using namespace functional::placeholder;

TEST(Functional_While, Runtime)
{
  ASSERT_TRUE(functional::While((_ < 10), 0, (_ + 1)) == 10);
}

TEST(Functional_While, Compiletime)
{
  ASSERT_TRUE(functional::While(integral::less.than(10_c), 0_c, integral::plus.by(1_c)) == 10_c);
}
