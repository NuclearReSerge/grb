#include "CLI/CmdAnalyzer.h"

#include "Main/AnalysisData.h"

#include "test/Mock/AnalyzerMock.h"
#include "test/Mock/CatalogMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace grb
{

class CmdAnalyzerMock : public CmdAnalyzer
{
public:
  Analyzer* createAnalyzerOriginal(const std::string& name)
  {
    return CmdAnalyzer::createAnalyzer(name);
  }

  void setAnalyzer(Analyzer* analyzer)
  {
    _analyzer = analyzer;
  }

protected:
  Analyzer* createAnalyzer(const std::string&)
  {
    return _analyzer;
  }

private:
  Analyzer* _analyzer;
};

} // namespace grb


namespace testing
{

class CmdAnalyzerTest : public Test
{
public:

protected:
  void SetUp()
  {
    _analyzer = new grb::AnalyzerMock(grb::type::UNDEFINED_ANALYZER);
    _analyzer->setConfigured();
    _catalogData = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
    _catalogModel = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
    grb::AnalysisData::instance()->setAnalyzer(_analyzer);
    grb::AnalysisData::instance()->setCatalogData(_catalogData);
    grb::AnalysisData::instance()->setCatalogModel(_catalogModel);
  }
  void TearDown()
  {
    grb::AnalysisData::instance()->clear();
  }

  void callParse()
  {
    try
    {
      _result = _cmd.parse(_tokens);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  void callExecute()
  {
    try
    {
      _cmd.execute();
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _result { false };
  bool _thrown { false };
  grb::CmdAnalyzerMock _cmd;

  grb::AnalyzerMock* _analyzer { nullptr };
  grb::CatalogMock* _catalogData { nullptr };
  grb::CatalogMock* _catalogModel { nullptr };
  std::list<std::string> _tokens { "undefined-analyzer-cmd" };
};

TEST_F(CmdAnalyzerTest, init)
{
  ASSERT_EQ(grb::type::CMD_ANALYZER, _cmd.getType());
}

TEST_F(CmdAnalyzerTest, parse_emptyTokens)
{
  _tokens.clear();
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, parse_AnalyzerParseTrue)
{
  EXPECT_CALL(*_analyzer, doParse(_))
      .WillOnce(Return(true));

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdAnalyzerTest, parse_AnalyzerParseFalse)
{
  EXPECT_CALL(*_analyzer, doParse(_))
      .WillOnce(Return(false));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, parse_AnalyzerUnknownAnalyzerCmd)
{
  _tokens.clear();
  _tokens.push_back("analyzer-cmd");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, parse_noAnalyzerNoCatalogData)
{
  grb::AnalysisData::instance()->setAnalyzer(nullptr);
  grb::AnalysisData::instance()->setCatalogData(nullptr);

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, parse_noAnalyzer_createAnalyzerFailed)
{
  grb::AnalysisData::instance()->setAnalyzer(nullptr);
  _cmd.setAnalyzer(nullptr);

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, parse_noAnalyzer)
{
  grb::AnalysisData::instance()->setAnalyzer(nullptr);
  _analyzer = new grb::AnalyzerMock(grb::type::UNDEFINED_ANALYZER);
  _cmd.setAnalyzer(_analyzer);

  EXPECT_CALL(*_analyzer, doParse(_))
      .WillOnce(Return(true));

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdAnalyzerTest, execute_AnalyzerNotConfigured)
{
  grb::AnalysisData::instance()->getAnalyzer()->setConfigured(false);

  callExecute();

  ASSERT_FALSE(_thrown);
}

TEST_F(CmdAnalyzerTest, execute_NoCatalogModel)
{
  grb::AnalysisData::instance()->setCatalogModel(nullptr);

  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdAnalyzerTest, execute)
{
  EXPECT_CALL(*_analyzer, doExecute())
      .Times(1);

  callExecute();

  ASSERT_FALSE(_thrown);
}

TEST_F(CmdAnalyzerTest, help_short)
{
  ASSERT_FALSE(_cmd.help(grb::type::HELP_SHORT).empty());
}

TEST_F(CmdAnalyzerTest, help_long)
{
  ASSERT_FALSE(_cmd.help(grb::type::HELP_LONG).empty());
}

TEST_F(CmdAnalyzerTest, createAnalyzer)
{
  ASSERT_EQ(nullptr, _cmd.createAnalyzerOriginal("undefined-analyzer"));
}

} // namespace testing
