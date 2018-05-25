#include <blackmagic/functional/functional.hpp>
#include <blackmagic/integral/integral.hpp>

#include <gtest/gtest.h>

namespace functional = blackmagic::functional;
namespace integral   = blackmagic::integral;
using namespace blackmagic::integral::literals;

struct S {
  operator bool() const
  {
    return true;
  }
};

TEST(Functional_If, RuntimeDispatch)
{
  ASSERT_TRUE(functional::If(true, 5, 8) == 5);
  ASSERT_TRUE(functional::If(S{}, 5, 8) == 5);
}

TEST(Functional_If, CompileTimeDispatch)
{
  ASSERT_TRUE(functional::If("false"_bc, 5, 8.0) == 8.0);
}
