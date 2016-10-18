#include "CLI/CmdCorrelation.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdCorrelationTest : public Test
{
protected:
  grb::CmdCorrelation _cmd;
  std::list<std::string> _tokens { "token" };
};

TEST_F(CmdCorrelationTest, init)
{
  ASSERT_EQ(grb::type::CMD_CORRELATION, _cmd.getType());
}

TEST_F(CmdCorrelationTest, parse)
{
  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_TRUE(_tokens.empty());
}

TEST_F(CmdCorrelationTest, execute)
{
  _cmd.execute();
}

TEST_F(CmdCorrelationTest, help_short)
{
  _cmd.help(grb::type::HELP_SHORT);
}

TEST_F(CmdCorrelationTest, help_long)
{
  _cmd.help(grb::type::HELP_LONG);
}

} // namespace testing
