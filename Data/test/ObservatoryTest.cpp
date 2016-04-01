#include "Data/Observatory.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

class ObservatoryTest : public Test
{
};

TEST_F(ObservatoryTest, isPresent_Positive)
{
  ASSERT_EQ(true, Observatory::instance()->isPresent("APEX"));
  ASSERT_EQ(true, Observatory::instance()->isPresent("WXM-HETE2"));
}

TEST_F(ObservatoryTest, isPresent_Negative)
{
  ASSERT_EQ(false, Observatory::instance()->isPresent(""));
  ASSERT_EQ(false, Observatory::instance()->isPresent("#"));
}

TEST_F(ObservatoryTest, getIndex_Positive)
{
  ASSERT_EQ((int) 0, Observatory::instance()->getIndex("APEX"));
  ASSERT_EQ((int) 35, Observatory::instance()->getIndex("WXM-HETE2"));
}

TEST_F(ObservatoryTest, getIndex_Negative)
{
  ASSERT_EQ((int) -1, Observatory::instance()->getIndex(""));
  ASSERT_EQ((int) -1, Observatory::instance()->getIndex("#"));
}

TEST_F(ObservatoryTest, getName_Positive)
{
  ASSERT_STREQ("APEX", Observatory::instance()->getName(0).c_str());
  ASSERT_STREQ("WXM-HETE2", Observatory::instance()->getName(35).c_str());
}

TEST_F(ObservatoryTest, getName_Negative)
{
  ASSERT_STREQ(NAME_NA.c_str(), Observatory::instance()->getName(-1).c_str());
  ASSERT_STREQ(NAME_NA.c_str(), Observatory::instance()->getName(36).c_str());
}

TEST_F(ObservatoryTest, getDescription)
{
  ASSERT_EQ(false, Observatory::instance()->getDescription().empty());
}

} // namespace test
} // namespace grb
