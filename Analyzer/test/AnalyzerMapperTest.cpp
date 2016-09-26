#include "Analyzer/AnalyzerMapper.h"

#include <gtest/gtest.h>

namespace testing
{

class AnalyzerMapperTest : public Test
{
protected:
  void printWhat(grb::Exception& /*exc*/)
  {
    //std::cout << exc.what() << std::endl;
  }
};

TEST_F(AnalyzerMapperTest, isPresent_Positive)
{
  ASSERT_TRUE(grb::AnalyzerMapper::instance()->isPresent("undefined-analyzer"));
}

TEST_F(AnalyzerMapperTest, isPresent_Negative)
{
  ASSERT_FALSE(grb::AnalyzerMapper::instance()->isPresent("analyzer-name"));
}

TEST_F(AnalyzerMapperTest, getValue_Positive)
{
  ASSERT_EQ((grb::type::AnalyzerType) grb::type::UNDEFINED_ANALYZER,
            grb::AnalyzerMapper::instance()->getValue("undefined-analyzer"));
}

TEST_F(AnalyzerMapperTest, getValue_Negative)
{
  try
  {
    grb::AnalyzerMapper::instance()->getValue("analyzer-name");
  }
  catch (grb::Exception exc)
  {
    printWhat(exc);
  }
}

TEST_F(AnalyzerMapperTest, getKey_Positive)
{
  ASSERT_STREQ("undefined-analyzer",
               grb::AnalyzerMapper::instance()->getKey(grb::type::UNDEFINED_ANALYZER).c_str());
}

TEST_F(AnalyzerMapperTest, getKey_Negative)
{
  try
  {
    grb::AnalyzerMapper::instance()->getKey((grb::type::AnalyzerType) -1);
  }
  catch (grb::Exception exc)
  {
    printWhat(exc);
  }
}

} // namespace testing
