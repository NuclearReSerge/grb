#include "Data/TimeDef.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

class TimeDefTest : public Test
{
};

TEST_F(TimeDefTest, isPresent_Positive)
{
  ASSERT_EQ(true, TimeDef::instance()->isPresent("BAT trigger"));
  ASSERT_EQ(true, TimeDef::instance()->isPresent("Trigger time"));
}

TEST_F(TimeDefTest, isPresent_Negative)
{
  ASSERT_EQ(false, TimeDef::instance()->isPresent(""));
  ASSERT_EQ(false, TimeDef::instance()->isPresent("#"));
}

TEST_F(TimeDefTest, getIndex_Positive)
{
  ASSERT_EQ((int) 0, TimeDef::instance()->getIndex("BAT trigger"));
  ASSERT_EQ((int) 6, TimeDef::instance()->getIndex("Trigger time"));
}

TEST_F(TimeDefTest, getIndex_Negative)
{
  ASSERT_EQ((int) -1, TimeDef::instance()->getIndex(""));
  ASSERT_EQ((int) -1, TimeDef::instance()->getIndex("#"));
}

TEST_F(TimeDefTest, getName_Positive)
{
  ASSERT_STREQ("BAT trigger", TimeDef::instance()->getName(0).c_str());
  ASSERT_STREQ("Trigger time", TimeDef::instance()->getName(6).c_str());
}

TEST_F(TimeDefTest, getName_Negative)
{
  ASSERT_STREQ(NAME_NA.c_str(), TimeDef::instance()->getName(-1).c_str());
  ASSERT_STREQ(NAME_NA.c_str(), TimeDef::instance()->getName(12).c_str());
}

TEST_F(TimeDefTest, getDescription)
{
  ASSERT_EQ(false, TimeDef::instance()->getDescription().empty());
}

} // namespace test
} // namespace grb
