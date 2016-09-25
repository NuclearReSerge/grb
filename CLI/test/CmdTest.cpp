#include "test/Mock/CmdMock.h"

#include <gtest/gtest.h>

namespace testing
{

class CmdTest : public Test
{
public:
  bool parseAllTrue(std::list<std::string>& tokens)
  {
    tokens.clear();
    return true;
  }
  bool parseAllFalse(std::list<std::string>& tokens)
  {
    tokens.clear();
    return false;
  }
  bool parseNoneTrue(std::list<std::string>& )
  {
    return true;
  }
  bool parseNoneFalse(std::list<std::string>& )
  {
    return false;
  }
  bool parseThrow(std::list<std::string>& )
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL + grb::type::EXCEPTION_MOD_NO_PREFIX,
                       "parseThrow");
    throw exc;
  }
  void executeNoThrow()
  {
  }
  void executeThrow()
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL + grb::type::EXCEPTION_MOD_NO_PREFIX,
                       "executeThrow");
    throw exc;
  }
  std::string help(grb::type::CommandHelpType type)
  {
    switch (type)
    {
      case grb::type::HELP_SHORT:
      {
        ++_helpShort;
        return "short help";
      }
      case grb::type::HELP_LONG:
      {
        ++_helpLong;
        return "long help";
      }
      case grb::type::HELP_FULL:
      {
        ++_helpFull;
        return "full help";
      }
      default:
        break;
    }
    return "unknown help";
  }


protected:
  void printWhat(grb::Exception& /*exc*/)
  {
    // std::cout << exc.what() << std::endl;
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
  int _helpShort { 0 };
  int _helpLong { 0 };
  int _helpFull { 0 };
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
  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseAllTrue));

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdTest, parseAllFalse)
{
  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseAllFalse));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdTest, parseNoneFalse)
{
  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseNoneFalse));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdTest, parseNoneTrue)
{
  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseNoneTrue));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdTest, parseThrow)
{
  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseThrow));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdTest, executeNoThrow)
{
  EXPECT_CALL(_cmd, doExecute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::executeNoThrow));

  callExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_cmd.wasExecuted());
}

TEST_F(CmdTest, executeThrow)
{
  EXPECT_CALL(_cmd, doExecute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::executeThrow));

  callExecute();

  ASSERT_TRUE(_thrown);
  ASSERT_FALSE(_cmd.wasExecuted());
}

TEST_F(CmdTest, helpShort)
{
  EXPECT_CALL(_cmd, doHelp(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::help));

  ASSERT_NO_THROW(_cmd.help());

  ASSERT_EQ(1, _helpShort);
  ASSERT_EQ(0, _helpLong);
  ASSERT_EQ(0, _helpFull);
}

TEST_F(CmdTest, helpLong)
{
  EXPECT_CALL(_cmd, doHelp(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::help));

  ASSERT_NO_THROW(_cmd.help(grb::type::HELP_LONG));

  ASSERT_EQ(0, _helpShort);
  ASSERT_EQ(1, _helpLong);
  ASSERT_EQ(0, _helpFull);
}

TEST_F(CmdTest, helpFull)
{
  EXPECT_CALL(_cmd, doHelp(_))
      .Times(2)
      .WillRepeatedly(Invoke(this, &CmdTest::help));

  ASSERT_NO_THROW(_cmd.help(grb::type::HELP_FULL));

  ASSERT_EQ(1, _helpShort);
  ASSERT_EQ(1, _helpLong);
  ASSERT_EQ(0, _helpFull);
}

} // namespace testing
