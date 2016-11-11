#include "Analyzer/AnalyzerGrbcat.h"

#include "Analyzer/AnalyzerCmdMapper.h"
#include "Catalog/CatalogEntryGrbcat.h"
#include "Correlation/CorrelationMapper.h"
#include "Main/AnalysisData.h"
#include "Model/IsotropicSphereModel.h"

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
    grb::AnalysisData::instance()->setCatalogData(new grb::CatalogMock(grb::type::GRBCAT));
    grb::AnalysisData::instance()->setCatalogModel(new grb::CatalogMock(grb::type::GRBCAT));
    grb::AnalysisData::instance()->setCorrelation(new grb::CorrelationMock(grb::type::CORRELATION_GRBCAT_DTDARC));
    grb::AnalysisData::instance()->setModel(new grb::IsotropicSphereModel());
  }

  void TearDown()
  {
    grb::AnalysisData::instance()->clear();
  }

  void callParseAndExecute()
  {
    try
    {
      _result = _analyzer.parse(_cmd, _tokens);
      if (_result)
        _analyzer.execute(_cmd);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  std::list<std::string> _tokens;
  bool _result = false;
  bool _thrown = false;
  std::string _filePrefix;
  grb::AnalyzerGrbcat _analyzer;
  grb::type::AnalyzerCmdType _cmd = grb::type::UNDEFINED_ANALYZER_CMD;
};

TEST_F(AnalyzerGrbcatTest, initial)
{
  ASSERT_EQ(grb::type::GRBCAT_ANALYZER, _analyzer.getType());
  ASSERT_FALSE(_analyzer.isConfigurationValid());
}

TEST_F(AnalyzerGrbcatTest, nothingToParse)
{
  callParseAndExecute();

  ASSERT_FALSE(_result);
}

TEST_F(AnalyzerGrbcatTest, unknownSubCmd)
{
  _cmd = grb::type::UNDEFINED_ANALYZER_CMD;

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
  _cmd = grb::type::ANALYZER_CREATE;

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, create_unknownCorrelation)
{
  _cmd = grb::type::ANALYZER_CREATE;
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
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG));
  grb::AnalysisData::instance()->setCatalogModel(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG));
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
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG));
  callParseAndExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerGrbcatTest, wrongCatalogModel)
{
  _tokens.push_back("set");
  _tokens.push_back("dummy");
  grb::AnalysisData::instance()->setCatalogModel(
        new grb::CatalogMock(grb::type::UNDEFINED_CATALOG));
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

  EXPECT_CALL(*corr, doParse(_,_))
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

  EXPECT_CALL(*corr, doParse(_,_))
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

} // namespace testing
