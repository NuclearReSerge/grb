#include "Data/Reference.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

class ReferenceTest : public Test
{
};

TEST_F(ReferenceTest, isPresent_Positive)
{
  ASSERT_EQ(true, Reference::instance()->isPresent("1974ApJ...188L...1S"));
  ASSERT_EQ(true, Reference::instance()->isPresent("Mitrofanov et al. (1990)"));
}

TEST_F(ReferenceTest, isPresent_Negative)
{
  ASSERT_EQ(false, Reference::instance()->isPresent(""));
  ASSERT_EQ(false, Reference::instance()->isPresent("#"));
}

TEST_F(ReferenceTest, getIndex_Positive)
{
  ASSERT_EQ((int) 0, Reference::instance()->getIndex("1974ApJ...188L...1S"));
  ASSERT_EQ((int) 329, Reference::instance()->getIndex("Mitrofanov et al. (1990)"));
}

TEST_F(ReferenceTest, getIndex_Negative)
{
  ASSERT_EQ((int) -1, Reference::instance()->getIndex(""));
  ASSERT_EQ((int) -1, Reference::instance()->getIndex("#"));
}

TEST_F(ReferenceTest, getName_Positive)
{
  ASSERT_STREQ("1974ApJ...188L...1S", Reference::instance()->getName(0).c_str());
  ASSERT_STREQ("Mitrofanov et al. (1990)", Reference::instance()->getName(329).c_str());
}

TEST_F(ReferenceTest, getName_Negative)
{
  ASSERT_STREQ(NAME_NA.c_str(), Reference::instance()->getName(-1).c_str());
  ASSERT_STREQ(NAME_NA.c_str(), Reference::instance()->getName(342).c_str());
}

TEST_F(ReferenceTest, getDescription)
{
  ASSERT_EQ(false, Reference::instance()->getDescription().empty());
}

} // namespace test
} // namespace grb
