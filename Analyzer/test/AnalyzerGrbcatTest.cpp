#include "Analyzer/AnalyzerGrbcat.h"

#include "Analyzer/AnalyzerCmdMapper.h"
#include "Correlation/CorrelationMapper.h"
#include "Data/CatalogEntryGrbcat.h"
#include "Main/AnalysisData.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/CorrelationMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace testing
{

class AnalyzerGrbcatTest : public Test
{
public:
  bool correlationSave(const std::string& filename)
  {
    return _filePrefix == filename;
  }

protected:
  void SetUp()
  {
    grb::AnalysisData::instance()->setCatalogData(
          new grb::CatalogMock(grb::type::GRBCAT_ENTRY));

    grb::AnalysisData::instance()->setCatalogModel(
          new grb::CatalogMock(grb::type::GRBCAT_ENTRY));

    grb::AnalysisData::instance()->setCorrelation(
          new grb::CorrelationMock(grb::type::CORRELATION_GRBCAT_DTDARC));
  }

  void TearDown()
  {
    grb::AnalysisData::instance()->clear();
  }

  void callParseAndExecute()
  {
    try
    {
      _result = _analyzer.parse(_tokens);
      _analyzer.execute();
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  std::list<std::string> _tokens;
  bool _result { false };
  bool _thrown { false };
  std::string _filePrefix { "prefix" };
  grb::AnalyzerGrbcat _analyzer;
};

TEST_F(AnalyzerGrbcatTest, initial)
{
  ASSERT_EQ(grb::type::GRBCAT_ANALYZER, _analyzer.getType());
  ASSERT_FALSE(_analyzer.isConfigured());
}

TEST_F(AnalyzerGrbcatTest, nothingToParse)
{
  callParseAndExecute();

  ASSERT_FALSE(_result);
}

TEST_F(AnalyzerGrbcatTest, unknownSubCmd)
{
  _tokens.push_back("command-name");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, unhandledSubCmd)
{
  _tokens.push_back(grb::AnalyzerCmdMapper::instance()->getKey(grb::type::UNDEFINED_ANALYZER_CMD));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, create_noArgument)
{
  _tokens.push_back("create");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, create_unknownCorrelation)
{
  _tokens.push_back("create");
  _tokens.push_back("correlation-name");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, create_invalidCorrelation)
{
  _tokens.push_back("create");
  _tokens.push_back(grb::CorrelationMapper::instance()->getKey(grb::type::UNDEFINED_CORRELATION));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, create_validCorrelation)
{
  _tokens.push_back("create");
  _tokens.push_back(grb::CorrelationMapper::instance()->getKey(grb::type::CORRELATION_GRBCAT_DTDARC));
  grb::AnalysisData::instance()->setCorrelation(nullptr);

  callParseAndExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_result);
  ASSERT_EQ(0, _tokens.size());
  ASSERT_NE(nullptr, grb::AnalysisData::instance()->getCorrelation());
}

TEST_F(AnalyzerGrbcatTest, wrongAnalysisData)
{
  _tokens.push_back("set");
  _tokens.push_back("dummy");
  grb::AnalysisData::instance()->setCatalogData(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG_ENTRY));
  grb::AnalysisData::instance()->setCatalogModel(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG_ENTRY));
  grb::AnalysisData::instance()->setCorrelation(
        new grb::CorrelationMock(grb::type::UNDEFINED_CORRELATION));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, wrongCatalogData)
{
  _tokens.push_back("set");
  _tokens.push_back("dummy");
  grb::AnalysisData::instance()->setCatalogData(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG_ENTRY));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, wrongCatalogModel)
{
  _tokens.push_back("set");
  _tokens.push_back("dummy");
  grb::AnalysisData::instance()->setCatalogModel(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG_ENTRY));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, wrongCorrelation)
{
  _tokens.push_back("set");
  _tokens.push_back("dummy");
  grb::AnalysisData::instance()->setCorrelation(
        new grb::CorrelationMock(grb::type::UNDEFINED_CORRELATION));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, set_noArgument)
{
  _tokens.push_back("set");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, set_CorrelationParseFalse)
{
  _tokens.push_back("set");
  _tokens.push_back("default");
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, parse(_))
          .WillOnce(Return(false));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, set_CorrelationParseTrue)
{
  _tokens.push_back("set");
  _tokens.push_back("default");
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, parse(_))
          .WillOnce(Return(true));

  callParseAndExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_result);
}

TEST_F(AnalyzerGrbcatTest, build_notConfigured)
{
  _tokens.push_back("build");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, build_CorrelationBuildFalse)
{
  _tokens.push_back("build");
  _analyzer.setConfigured();
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, build(_,_))
          .WillOnce(Return(false));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, build_CorrelationBuildTrue)
{
  _tokens.push_back("build");
  _analyzer.setConfigured();
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, build(_,_))
          .WillOnce(Return(true));

  callParseAndExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_result);
}

TEST_F(AnalyzerGrbcatTest, save_CorrelationSaveFalse)
{
  _tokens.push_back("save");
  _analyzer.setConfigured();
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, save(_))
          .WillOnce(Return(false));

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, save_CorrelationSaveTrue)
{
  _tokens.push_back("save");
  _analyzer.setConfigured();
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, save(_))
          .WillOnce(Return(true));

  callParseAndExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_result);
}

TEST_F(AnalyzerGrbcatTest, save_customFilePrefix)
{
  _tokens.push_back("save");
  _tokens.push_back(_filePrefix);
  _analyzer.setConfigured();
  grb::CorrelationMock* corr = static_cast<grb::CorrelationMock*>(
        grb::AnalysisData::instance()->getCorrelation());

  EXPECT_CALL(*corr, save(_))
          .WillOnce(Invoke(this, &AnalyzerGrbcatTest::correlationSave));

  callParseAndExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_result);
}

} // namespace testing
