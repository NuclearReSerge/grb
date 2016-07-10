#include "CLI/CmdFactory.h"

#include "CLI/CmdAnalyzer.h"
#include "CLI/CmdCorrelation.h"
#include "CLI/CmdDatabase.h"
#include "CLI/CmdFilter.h"
#include "CLI/CmdHelp.h"
#include "CLI/CmdModel.h"
#include "CLI/CmdQuit.h"

namespace grb
{

namespace factory
{

Cmd*
CmdFactory::create(CommandLine& cli, const type::CommandType type)
{
  switch (type)
  {
    case type::CMD_EXIT:
      return new CmdQuit(cli, type::CMD_EXIT);
    case type::CMD_QUIT:
      return new CmdQuit(cli);
    case type::CMD_HELP:
      return new CmdHelp(cli);
    case type::CMD_DATABASE:
      return new CmdDatabase(cli);
    case type::CMD_MODEL:
      return new CmdModel(cli);
    case type::CMD_FILTER:
      return new CmdFilter(cli);
    case type::CMD_CORRELATION:
      return new CmdCorrelation(cli);
    case type::CMD_ANALYZER:
      return new CmdAnalyzer(cli);
    default:
      break;
  }
  return nullptr;
}

Cmd*
CmdFactory::create(CommandLine& cli, const std::string& name)
{
  type::CommandType cmdType;
  try
  {
    cmdType = CmdMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(cli, cmdType);
}

}

}
