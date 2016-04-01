#include "Data/TimeMod.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

class TimeModTest : public Test
{
};

TEST_F(TimeModTest, isPresent_Positive)
{
  ASSERT_EQ(true, Time50Mod::instance()->isPresent("<"));
  ASSERT_EQ(true, Time50Mod::instance()->isPresent("~"));
}

TEST_F(TimeModTest, isPresent_Negative)
{
  ASSERT_EQ(false, Time50Mod::instance()->isPresent(""));
  ASSERT_EQ(false, Time50Mod::instance()->isPresent("#"));
}

TEST_F(TimeModTest, getIndex_Positive)
{
  ASSERT_EQ((int) 0, Time50Mod::instance()->getIndex("<"));
  ASSERT_EQ((int) 2, Time50Mod::instance()->getIndex("~"));
}

TEST_F(TimeModTest, getIndex_Negative)
{
  ASSERT_EQ((int) -1, Time50Mod::instance()->getIndex(""));
  ASSERT_EQ((int) -1, Time50Mod::instance()->getIndex("#"));
}

TEST_F(TimeModTest, getName_Positive)
{
  ASSERT_STREQ("<", Time50Mod::instance()->getName(0).c_str());
  ASSERT_STREQ("~", Time50Mod::instance()->getName(2).c_str());
}

TEST_F(TimeModTest, getName_Negative)
{
  ASSERT_STREQ(NAME_NA.c_str(), Time50Mod::instance()->getName(-1).c_str());
  ASSERT_STREQ(NAME_NA.c_str(), Time50Mod::instance()->getName(3).c_str());
}

TEST_F(TimeModTest, getDescription)
{
  ASSERT_EQ(false, Time50Mod::instance()->getDescription().empty());
}

} // namespace test
} // namespace grb

