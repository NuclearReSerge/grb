#include "Main/Init.h"

#include <gtest/gtest.h>

namespace testing
{

class InitTest : public Test
{
};

TEST_F(InitTest, intro)
{
  grb::Init::intro();
}

TEST_F(InitTest, usage)
{
  grb::Init::usage("bin-name");
}

} // namespace testing
