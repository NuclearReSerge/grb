#include "CLI/CommandLine.h"
#include "CLI/CommandMapper.h"

#include "test/Mock/CmdMock.h"

#include <gtest/gtest.h>
#include <memory>

namespace
{

const int ARGC = 3;

char ARG0[] = "BINARY";
char ARG1[] = "ARG_1";
char ARG2[] = "ARG_2";

char* ARGV[] = { ARG0, ARG1, ARG2, nullptr };

} // namespace

namespace grb
{

class CommandLineMock : public CommandLine
{
public:
  CommandLineMock(int argc, char** argv)
    : CommandLine(argc, argv), _cmd(new grb::CmdMock(grb::type::UNDEFINED_COMMAND))
  {
  }

  ~CommandLineMock()
  {
    if (!_created)
    {
      delete _cmd;
      _cmd = nullptr;
    }
  }

  CmdMock*& getCmdMock()
  {
    return _cmd;
  }

protected:
  Cmd* createCommand(const std::string& /*name*/) override
  {
    _created = true;
    return _cmd;
  }

private:
  bool _created { false };
  CmdMock* _cmd;
};

} // namespace grb

namespace testing
{

class CommandLineTest : public Test
{
public:
  bool parseAllTrue(std::list<std::string>& tokens)
  {
    tokens.clear();
    return true;
  }
  bool parseTrue(std::list<std::string>& )
  {
    return true;
  }
  bool parseFalse(std::list<std::string>& )
  {
    return false;
  }
  bool parseThrow(std::list<std::string>& )
  {
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL + grb::type::EXCEPTION_MOD_NO_PREFIX,
                       "parseTrueThrow");
    throw exc;
  }

protected:
  void SetUp()
  {
  }
  void TearDown()
  {
  }

  void printWhat(grb::Exception& /*exc*/)
  {
    // std::cout << exc.what() << std::endl;
  }

  void callParse()
  {
    try
    {
      _cmd = _cli.parse(_tokens);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _thrown { false };
  std::list<std::string> _tokens { "command-name" };
  grb::Cmd* _cmd { nullptr };
  grb::CommandLineMock _cli { ARGC, ARGV };
};

TEST_F(CommandLineTest, getBinaryName_noArgcNoArgv)
{
  grb::CommandLineMock cli(0, nullptr);
    ASSERT_STREQ("", cli.getBinaryName().c_str());
}

TEST_F(CommandLineTest, getBinaryName_ArgcArgv)
{
  ASSERT_STREQ(ARG0, _cli.getBinaryName().c_str());
}

TEST_F(CommandLineTest, getPrompt)
{
  std::string prompt = grb::CMD_PROMPT + "> ";
  std::string prompt0 = grb::CMD_PROMPT + "[0]> ";
  std::string prompt1 = grb::CMD_PROMPT + "[1]> ";

  ASSERT_STREQ(prompt.c_str(), _cli.getPrompt(false).c_str());
  ASSERT_STREQ(prompt0.c_str(), _cli.getPrompt().c_str());
  _cli.incCmdIdx();
  ASSERT_STREQ(prompt1.c_str(), _cli.getPrompt().c_str());
}

TEST_F(CommandLineTest, quit)
{
  ASSERT_FALSE(_cli.quit());
  _cli.setQuit();
  ASSERT_TRUE(_cli.quit());
}

TEST_F(CommandLineTest, parse_CmdParseAllTrue)
{
  EXPECT_CALL(*_cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseAllTrue));

  callParse();

  ASSERT_FALSE(_thrown);
  ASSERT_NE((grb::Cmd*) nullptr, _cmd);
  ASSERT_EQ(&_cli, _cmd->getCLI());
}

TEST_F(CommandLineTest, parse_NothingToParse)
{
  _tokens.clear();

  callParse();

  ASSERT_FALSE(_thrown);
  ASSERT_EQ((grb::Cmd*) nullptr, _cmd);
}

TEST_F(CommandLineTest, parse_CommandNotCreated)
{
  delete _cli.getCmdMock();
  _cli.getCmdMock() = nullptr;

  callParse();

  ASSERT_FALSE(_thrown);
  ASSERT_EQ((grb::Cmd*) nullptr, _cmd);
}

TEST_F(CommandLineTest, parse_CmdParseFalse)
{
  EXPECT_CALL(*_cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseFalse));

  callParse();

  ASSERT_FALSE(_thrown);
  ASSERT_EQ((grb::Cmd*) nullptr, _cmd);
}

TEST_F(CommandLineTest, parse_CmdParseTrue_AgrumentsLeft)
{
  _tokens.push_back("left-arg");

  EXPECT_CALL(*_cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseTrue));

  callParse();

  ASSERT_TRUE(_thrown);
  ASSERT_EQ((grb::Cmd*) nullptr, _cmd);
}

TEST_F(CommandLineTest, parse_CmdParseThrow)
{
  EXPECT_CALL(*_cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseThrow));

  callParse();

  ASSERT_TRUE(_thrown);
  ASSERT_EQ((grb::Cmd*) nullptr, _cmd);
}

} // namespace testing
