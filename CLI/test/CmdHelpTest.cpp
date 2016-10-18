#include "CLI/CmdHelp.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdHelpTest : public Test
{
protected:
  grb::CmdHelp _cmd;
  std::list<std::string> _tokens { "help" };
};

TEST_F(CmdHelpTest, init)
{
  ASSERT_EQ(grb::type::CMD_HELP, _cmd.getType());
}

TEST_F(CmdHelpTest, parse_ShowAll)
{
  _tokens.clear();

  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_TRUE(_tokens.empty());
  ASSERT_TRUE(_cmd.showAll());
  ASSERT_TRUE(_cmd.getSpecific().empty());
}

TEST_F(CmdHelpTest, parse_ShowSpecificPositive)
{
  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_TRUE(_tokens.empty());
  ASSERT_FALSE(_cmd.showAll());
  ASSERT_STREQ("help", _cmd.getSpecific().c_str());
}

TEST_F(CmdHelpTest, parse_ShowSpecificNegative)
{
  _tokens.push_back("EXTRA");

  bool thrown = false;
  try
  {
    _cmd.parse(_tokens);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
    thrown = true;
  }

  ASSERT_TRUE(thrown);
  ASSERT_FALSE(_tokens.empty());
}

TEST_F(CmdHelpTest, execute_ShowAll)
{
  _cmd.execute();
}

TEST_F(CmdHelpTest, execute_ShowSpecificPositive)
{
  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_FALSE(_cmd.showAll());
  ASSERT_FALSE(_cmd.getSpecific().empty());
  _cmd.execute();
}

TEST_F(CmdHelpTest, execute_ShowSpecificNegative)
{
  _tokens.clear();
  _tokens.push_back("unknown");

  ASSERT_TRUE(_cmd.parse(_tokens));
  ASSERT_FALSE(_cmd.showAll());
  ASSERT_FALSE(_cmd.getSpecific().empty());
  _cmd.execute();
}

TEST_F(CmdHelpTest, help_short)
{
  _cmd.help(grb::type::HELP_SHORT);
}

TEST_F(CmdHelpTest, help_long)
{
  _cmd.help(grb::type::HELP_LONG);
}

} // namespace testing
