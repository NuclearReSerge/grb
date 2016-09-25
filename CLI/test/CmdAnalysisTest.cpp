#include "CLI/CmdAnalyzer.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdAnalyzerTest : public Test
{

};

TEST_F(CmdAnalyzerTest, init)
{

}

} // namespace testing


/*
TEST_F(AnalyzerGrbcatTest, noAnalysisData)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->clear();

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, noCatalogData)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->setCatalogData(nullptr);

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, noCatalogModel)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->setCatalogModel(nullptr);

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, noCorrelation)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->setCorrelation(nullptr);

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}
*/

/*
TEST_F(AnalyzerGrbcatTest, emptyAnalysisData)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->getCatalogData()->getEntries().clear();
  grb::AnalysisData::instance()->getCatalogModel()->getEntries().clear();

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, emptyCatalogData)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->getCatalogData()->clear();

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, emptyCatalogModel)
{
  _tokens.push_back("set");
  grb::AnalysisData::instance()->getCatalogModel()->clear();

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}
*/
