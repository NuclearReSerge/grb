#include "CLI/CommandFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class CommandFactoryTest :
    public FactoryTestFixturesBase<grb::type::CommandType, grb::CmdBase, grb::factory::CommandFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_COMMAND;
    _invalidName = "undefined-command";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(CommandFactoryTest)

namespace testing
{

TEST_F(CommandFactoryTest, createName_CmdExit)
{
  _validType = grb::type::CMD_EXIT;
  _validName = "exit";
  callCreateName();
}

TEST_F(CommandFactoryTest, createType_CmdExit)
{
  _validType = grb::type::CMD_EXIT;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdQuit)
{
  _validType = grb::type::CMD_QUIT;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdHelp)
{
  _validType = grb::type::CMD_HELP;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdDatabase)
{
  _validType = grb::type::CMD_DATABASE;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdModel)
{
  _validType = grb::type::CMD_MODEL;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdFilter)
{
  _validType = grb::type::CMD_FILTER;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdCorrelation)
{
  _validType = grb::type::CMD_CORRELATION;
  callCreateType();
}

TEST_F(CommandFactoryTest, createType_CmdAnalyzer)
{
  _validType = grb::type::CMD_ANALYZER;
  callCreateType();
}

} // namespace testing
