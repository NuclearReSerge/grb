#include "test/Mock/CmdMock.h"

#include <gtest/gtest.h>

namespace
{

const std::list<std::string> TOKENS
{
  "TOKEN_1",
  "TOKEN_2",
  "TOKEN_3"
};

} // namespace

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
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL, "parseThrow");
    throw exc;
  }
  void executeNoThrow()
  {
  }
  void executeThrow()
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL, "executeThrow");
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
  void printWhat(grb::Exception& /*exc*/)
  {
    //std::cout << exc.what() << std::endl;
  }

protected:
  grb::CmdMock _cmd;
  int _helpShort = 0;
  int _helpLong = 0;
  int _helpFull = 0;
};

TEST_F(CmdTest, newCommand)
{
  EXPECT_CALL(_cmd, doParse(_))
      .Times(0);
  EXPECT_CALL(_cmd, doExecute())
      .Times(0);
  EXPECT_CALL(_cmd, doHelp(_))
      .Times(0);

  ASSERT_EQ(grb::type::UNDEFINED_COMMAND, _cmd.getType());
  ASSERT_FALSE(_cmd.wasExecuted());
}

TEST_F(CmdTest, parseAllTrue)
{
  std::list<std::string> tokens = TOKENS;
  bool res = false;

  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseAllTrue));

  ASSERT_NO_THROW(res = _cmd.parse(tokens));
  ASSERT_TRUE(res);
  ASSERT_EQ((size_t)0, tokens.size());
}

TEST_F(CmdTest, parseAllFalse)
{
  std::list<std::string> tokens = TOKENS;
  bool res = false;

  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseAllFalse));

  ASSERT_NO_THROW(res = _cmd.parse(tokens));
  ASSERT_FALSE(res);
  ASSERT_EQ((size_t)0, tokens.size());
}

TEST_F(CmdTest, parseNoneFalse)
{
  std::list<std::string> tokens = TOKENS;
  bool res = false;

  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseNoneFalse));

  ASSERT_NO_THROW(res = _cmd.parse(tokens));
  ASSERT_FALSE(res);
  ASSERT_NE((size_t)0, tokens.size());
}

TEST_F(CmdTest, parseNoneTrue)
{
  std::list<std::string> tokens = TOKENS;

  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseNoneTrue));

  try
  {
    _cmd.parse(tokens);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  ASSERT_NE((size_t)0, tokens.size());
}

TEST_F(CmdTest, parseThrow)
{
  std::list<std::string> tokens = TOKENS;

  EXPECT_CALL(_cmd, doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::parseThrow));

  try
  {
    _cmd.parse(tokens);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  ASSERT_NE((size_t)0, tokens.size());
}

TEST_F(CmdTest, executeNoThrow)
{
  EXPECT_CALL(_cmd, doExecute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::executeNoThrow));

  ASSERT_NO_THROW(_cmd.execute());
  ASSERT_TRUE(_cmd.wasExecuted());
}

TEST_F(CmdTest, executeThrow)
{
  EXPECT_CALL(_cmd, doExecute())
      .Times(1)
      .WillOnce(Invoke(this, &CmdTest::executeThrow));

  try
  {
    _cmd.execute();
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

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
