#include "test/Mock/AnalyzerMock.h"

#include <gtest/gtest.h>

namespace testing
{

class AnalyzerTest : public Test
{

};

TEST_F(AnalyzerTest, initial)
{
  grb::AnalyzerMock analyzer;

  ASSERT_EQ(grb::type::UNDEFINED_ANALYZER, analyzer.getType());
  ASSERT_FALSE(analyzer.isConfigured());
}

TEST_F(AnalyzerTest, setConfigured)
{
  grb::AnalyzerMock analyzer;

  analyzer.setConfigured();

  ASSERT_TRUE(analyzer.isConfigured());
}

} // namespace testing
