#include "Data/Region.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

class RegionTest : public Test
{
};

TEST_F(RegionTest, isPresent_Positive)
{
  ASSERT_EQ(true, Region::instance()->isPresent("annulus"));
  ASSERT_EQ(true, Region::instance()->isPresent("irregular"));
}

TEST_F(RegionTest, isPresent_Negative)
{
  ASSERT_EQ(false, Region::instance()->isPresent(""));
  ASSERT_EQ(false, Region::instance()->isPresent("#"));
}

TEST_F(RegionTest, getIndex_Positive)
{
  ASSERT_EQ((int) 0, Region::instance()->getIndex("annulus"));
  ASSERT_EQ((int) 6, Region::instance()->getIndex("irregular"));
}

TEST_F(RegionTest, getIndex_Negative)
{
  ASSERT_EQ((int) -1, Region::instance()->getIndex(""));
  ASSERT_EQ((int) -1, Region::instance()->getIndex("#"));
}

TEST_F(RegionTest, getName_Positive)
{
  ASSERT_STREQ("annulus", Region::instance()->getName(0).c_str());
  ASSERT_STREQ("irregular", Region::instance()->getName(6).c_str());
}

TEST_F(RegionTest, getName_Negative)
{
  ASSERT_STREQ(NAME_NA.c_str(), Region::instance()->getName(-1).c_str());
  ASSERT_STREQ(NAME_NA.c_str(), Region::instance()->getName(12).c_str());
}

TEST_F(RegionTest, getDescription)
{
  ASSERT_EQ(false, Region::instance()->getDescription().empty());
}

} // namespace test
} // namespace grb
