#include "Analyzer/AnalyzerFactory.h"

#include <gtest/gtest.h>

namespace testing
{

class AnalyzerFactoryTest : public Test
{
protected:
  void TearDown()
  {
    delete _analyzer;
  }

  grb::Analyzer* _analyzer { nullptr };
};

TEST_F(AnalyzerFactoryTest, createType_Positive)
{
  _analyzer = grb::AnalyzerFactory::instance()->createType(grb::type::GRBCAT_ANALYZER);
  ASSERT_NE((grb::Analyzer*) nullptr, _analyzer);
}

TEST_F(AnalyzerFactoryTest, createType_Negative)
{
  _analyzer = grb::AnalyzerFactory::instance()->createType(grb::type::UNDEFINED_ANALYZER);
  ASSERT_EQ((grb::Analyzer*) nullptr, _analyzer);
}

TEST_F(AnalyzerFactoryTest, createName_Positive)
{
  _analyzer = grb::AnalyzerFactory::instance()->createName("grbcat-analyzer");
  ASSERT_NE((grb::Analyzer*) nullptr, _analyzer);
}

TEST_F(AnalyzerFactoryTest, createName_Negative)
{
  _analyzer = grb::AnalyzerFactory::instance()->createName("undefined-analyzer");
  ASSERT_EQ((grb::Analyzer*) nullptr, _analyzer);
}

} // namespace testing
