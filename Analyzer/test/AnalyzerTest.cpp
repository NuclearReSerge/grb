#include "Analyzer/AnalyzerCmdMapper.h"
#include "Common/Exception.h"

#include "test/Mock/AnalyzerMock.h"
#include "test/Mock/MockHelper.h"

#include <gtest/gtest.h>

namespace testing
{

class AnalyzerTest : public Test
{
public:
  void doExecuteWithThrow()
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL, "doExecuteWithThrow");
    throw exc;
  }

protected:
  void callParse()
  {
    try
    {
      _result = _analyzer.parse(_tokens);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _result { false };
  bool _thrown { false };
  std::list<std::string> _tokens;
  grb::AnalyzerMock _analyzer { grb::type::UNDEFINED_ANALYZER };
};

TEST_F(AnalyzerTest, initial)
{
  ASSERT_EQ(grb::type::UNDEFINED_ANALYZER, _analyzer.getType());
  ASSERT_FALSE(_analyzer.isConfigured());
  ASSERT_EQ(grb::type::UNDEFINED_ANALYZER_CMD, _analyzer.getCmdType());
}

TEST_F(AnalyzerTest, setConfigured)
{
  _analyzer.setConfigured();
  ASSERT_TRUE(_analyzer.isConfigured());
}

TEST_F(AnalyzerTest, parse_empty)
{
  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(AnalyzerTest, parse_unknownCommand)
{
  _tokens.push_back("command-name");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(AnalyzerTest, parse_validCommand_doParseTrue)
{
  _tokens.push_back(grb::AnalyzerCmdMapper::instance()->getKey(grb::type::UNDEFINED_ANALYZER_CMD));

  EXPECT_CALL(_analyzer, doParse(_))
      .WillOnce(Return(true));

  callParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(grb::type::UNDEFINED_ANALYZER_CMD, _analyzer.getCmdType());
}

TEST_F(AnalyzerTest, parse_validCommand_doParseFalse)
{
  _tokens.push_back(grb::AnalyzerCmdMapper::instance()->getKey(grb::type::UNDEFINED_ANALYZER_CMD));

  EXPECT_CALL(_analyzer, doParse(_))
      .WillOnce(Return(false));

  callParse();

  ASSERT_FALSE(_result);
  ASSERT_EQ(grb::type::UNDEFINED_ANALYZER_CMD, _analyzer.getCmdType());
}

TEST_F(AnalyzerTest, execute_doExecute_noThrow)
{
  EXPECT_CALL(_analyzer, doExecute())
      .Times(1);

  ASSERT_NO_THROW(_analyzer.execute());
}

TEST_F(AnalyzerTest, execute_doExecute_Throw)
{
  EXPECT_CALL(_analyzer, doExecute())
      .WillOnce(Invoke(this, &AnalyzerTest::doExecuteWithThrow));

  ASSERT_THROW(_analyzer.execute(), grb::Exception);
}

} // namespace testing
