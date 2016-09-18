#include "CLI/CommandLine.h"

#include "test/Mock/CmdMock.h"

#include <gtest/gtest.h>

namespace
{

const int ARGC = 3;

char ARG0[] = "BINARY";
char ARG1[] = "ARG_1";
char ARG2[] = "ARG_2";

char* ARGV[] = { ARG0, ARG1, ARG2, nullptr };

const std::string CMD_NAME = "command";

const std::list<std::string> TOKENS
{
  CMD_NAME,
  "TOKEN_1",
  "TOKEN_2"
};

} // namespace

namespace grb
{

class CommandLineMock : public CommandLine
{
public:
  CommandLineMock()
    : CommandLine(ARGC, ARGV)
  {
    _cmd = new CmdMock;
  }

  ~CommandLineMock()
  {
    // created commands are deleted in CommandLine::~CommandLine()
  }

  Cmd* createCommand(const std::string& name)
  {
    if (name == CMD_NAME)
      return _cmd;

    return nullptr;
  }

  CmdMock* getCmdMock()
  {
    return _cmd;
  }

private:
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
    grb::Exception exc(grb::type::EXCEPTION_CRITICAL, "parseTrueThrow");
    throw exc;
  }

  void printWhat(grb::Exception& /*exc*/)
  {
    //std::cout << exc.what() << std::endl;
  }

protected:
  void SetUp()
  {
  }
  void TearDown()
  {
  }
};

TEST_F(CommandLineTest, initial)
{
  grb::CommandLineMock cli;
  std::string prompt = grb::CMD_PROMPT + "> ";
  std::string prompt0 = grb::CMD_PROMPT + "[0]> ";
  std::string prompt1 = grb::CMD_PROMPT + "[1]> ";

  ASSERT_STREQ(ARG0, cli.getBinaryName().c_str());

  ASSERT_STREQ(prompt.c_str(), cli.getPrompt(false).c_str());
  ASSERT_STREQ(prompt0.c_str(), cli.getPrompt().c_str());
  cli.incCmdIdx();
  ASSERT_STREQ(prompt1.c_str(), cli.getPrompt().c_str());

  ASSERT_FALSE(cli.quit());
  cli.setQuit();
  ASSERT_TRUE(cli.quit());
}

TEST_F(CommandLineTest, parse_CmdParseAllTrue)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens = TOKENS;
  grb::Cmd* cmd = nullptr;

  EXPECT_CALL(*cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseAllTrue));

  ASSERT_NO_THROW(cmd = cli.parse(tokens));
  ASSERT_NE((grb::Cmd*) nullptr, cmd);
  ASSERT_EQ(&cli, cmd->getCLI());
  ASSERT_EQ(0, tokens.size());
}

TEST_F(CommandLineTest, parse_NothingToParse)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens;
  grb::Cmd* cmd = nullptr;

  ASSERT_NO_THROW(cmd = cli.parse(tokens));
  ASSERT_EQ((grb::Cmd*) nullptr, cmd);
}

TEST_F(CommandLineTest, parse_CommandNotCreated)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens = TOKENS;
  grb::Cmd* cmd = nullptr;

  tokens.front()="UNKNOWN";

  ASSERT_NO_THROW(cmd = cli.parse(tokens));
  ASSERT_EQ((grb::Cmd*) nullptr, cmd);
  ASSERT_EQ(tokens.size(), TOKENS.size());
}

TEST_F(CommandLineTest, parse_CmdParseFalse)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens = TOKENS;
  grb::Cmd* cmd = nullptr;

  EXPECT_CALL(*cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseFalse));

  ASSERT_NO_THROW(cmd = cli.parse(tokens));
  ASSERT_EQ((grb::Cmd*) nullptr, cmd);
  ASSERT_EQ(tokens.size(), TOKENS.size() - 1);
}

TEST_F(CommandLineTest, parse_CmdParseTrue_AgrumentsLeft)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens = TOKENS;
  grb::Cmd* cmd = nullptr;

  EXPECT_CALL(*cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseTrue));

  try
  {
    cmd = cli.parse(tokens);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  ASSERT_EQ((grb::Cmd*) nullptr, cmd);
  ASSERT_EQ(tokens.size(), TOKENS.size() - 1);
}

TEST_F(CommandLineTest, parse_CmdParseThrow)
{
  grb::CommandLineMock cli;
  std::list<std::string> tokens = TOKENS;
  grb::Cmd* cmd = nullptr;

  EXPECT_CALL(*cli.getCmdMock(), doParse(_))
      .Times(1)
      .WillOnce(Invoke(this, &CommandLineTest::parseThrow));

  try
  {
    cmd = cli.parse(tokens);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  ASSERT_EQ((grb::Cmd*) nullptr, cmd);
  ASSERT_EQ(tokens.size(), TOKENS.size() - 1);
}

} // namespace testing
