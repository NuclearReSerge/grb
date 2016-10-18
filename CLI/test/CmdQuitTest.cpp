#include "CLI/CmdQuit.h"
#include "CLI/CommandLine.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdQuitTest : public Test
{
protected:
  grb::CmdQuit _cmd;
  std::list<std::string> _tokens { "token1", "token2" };
};

TEST_F(CmdQuitTest, init)
{
  ASSERT_EQ(grb::type::CMD_QUIT, _cmd.getType());
}

TEST_F(CmdQuitTest, parse)
{
  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_TRUE(_tokens.empty());
}

TEST_F(CmdQuitTest, execute)
{
  const int argc = 1;
  char arg0[] = "ARG0";
  char* argv[] = { arg0, nullptr };
  grb::CommandLine cli(argc, argv);

  _cmd.setCLI(&cli);

  ASSERT_FALSE(cli.quit());
  _cmd.execute();
  ASSERT_TRUE(cli.quit());
}

TEST_F(CmdQuitTest, help_short)
{
  _cmd.help(grb::type::HELP_SHORT);
}

TEST_F(CmdQuitTest, help_long)
{
  _cmd.help(grb::type::HELP_LONG);
}

} // namespace testing
