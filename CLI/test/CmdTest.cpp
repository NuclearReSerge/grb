#include "test/Mock/CmdMock.h"
#include "test/Mock/MockHelper.h"

#include <gtest/gtest.h>

namespace testing
{

class CmdTest : public Test
{
public:
  bool doParseAllTrue(std::list<std::string>& tokens)
  {
    tokens.clear();
    return true;
  }
  bool doParseAllFalse(std::list<std::string>& tokens)
  {
    tokens.clear();
    return false;
  }
  bool doParseNoneTrue(std::list<std::string>& )
  {
    return true;
  }
  bool doParseNoneFalse(std::list<std::string>& )
  {
    return false;
  }
  bool doParseThrow(std::list<std::string>& )
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL + grb::type::EXCEPTION_MOD_NO_PREFIX,
                       "parseThrow");
    throw exc;
  }
  void doExecuteNoThrow()
  {
  }
  void doExecuteThrow()
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL + grb::type::EXCEPTION_MOD_NO_PREFIX,
                       "executeThrow");
    throw exc;
  }
  std::string doHelp(grb::type::CommandHelpType type)
  {
    std::string text;

    if (type == grb::type::HELP_SHORT)
    {
      ++_helpShort;
      text +=  "short help";
    }
    if (type == grb::type::HELP_LONG)
    {
      ++_helpLong;
      text += "long help";
    }
    return text;
  }

protected:
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
  int _helpShort { 0 };
  int _helpLong { 0 };
  std::list<std::string> _tokens { "arg1", "arg2" };
  grb::CmdMock _cmd { grb::type::UNDEFINED_COMMAND };
};

TEST_F(CmdTest, newCommand)
{
  ASSERT_EQ(grb::type::UNDEFINED_COMMAND, _cmd.getType());
  ASSERT_FALSE(_cmd.wasExecuted());
}

TEST_F(CmdTest, parseAllTrue)
{
  EXPECT_CALL(_cmd, parse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doParseAllTrue));

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdTest, parseAllFalse)
{
  EXPECT_CALL(_cmd, parse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doParseAllFalse));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdTest, parseNoneFalse)
{
  EXPECT_CALL(_cmd, parse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doParseNoneFalse));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdTest, parseNoneTrue)
{
  EXPECT_CALL(_cmd, parse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doParseNoneTrue));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdTest, parseThrow)
{
  EXPECT_CALL(_cmd, parse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doParseThrow));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdTest, executeNoThrow)
{
  EXPECT_CALL(_cmd, execute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doExecuteNoThrow));

  callExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_cmd.wasExecuted());
}

TEST_F(CmdTest, executeThrow)
{
  EXPECT_CALL(_cmd, execute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doExecuteThrow));

  callExecute();

  ASSERT_TRUE(_thrown);
  ASSERT_FALSE(_cmd.wasExecuted());
}

TEST_F(CmdTest, helpShort)
{
  EXPECT_CALL(_cmd, help(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doHelp));

  ASSERT_NO_THROW(_cmd.help(grb::type::HELP_SHORT));

  ASSERT_EQ(1, _helpShort);
  ASSERT_EQ(0, _helpLong);
}

TEST_F(CmdTest, helpLong)
{
  EXPECT_CALL(_cmd, help(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::doHelp));

  ASSERT_NO_THROW(_cmd.help(grb::type::HELP_LONG));

  ASSERT_EQ(0, _helpShort);
  ASSERT_EQ(1, _helpLong);
}

TEST_F(CmdTest, helpFull)
{
  EXPECT_CALL(_cmd, help(_))
      .Times(2)
      .WillRepeatedly(Invoke(this, &CmdTest::doHelp));

  ASSERT_NO_THROW(_cmd.help(grb::type::HELP_FULL));

  ASSERT_EQ(1, _helpShort);
  ASSERT_EQ(1, _helpLong);
}

} // namespace testing
