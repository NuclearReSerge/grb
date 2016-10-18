#include "CLI/CmdFilter.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdFilterTest : public Test
{
protected:
  grb::CmdFilter _cmd;
  std::list<std::string> _tokens { "token" };
};

TEST_F(CmdFilterTest, init)
{
  ASSERT_EQ(grb::type::CMD_FILTER, _cmd.getType());
}

TEST_F(CmdFilterTest, parse)
{
  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_TRUE(_tokens.empty());
}

TEST_F(CmdFilterTest, execute)
{
  _cmd.execute();
}

TEST_F(CmdFilterTest, help_short)
{
  _cmd.help(grb::type::HELP_SHORT);
}

TEST_F(CmdFilterTest, help_long)
{
  _cmd.help(grb::type::HELP_LONG);
}

} // namespace testing
