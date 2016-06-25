#include "CLI/CommandFactory.h"
#include "CLI/CommandMapper.h"

#include "CLI/CmdQuit.h"
#include "CLI/CmdHelp.h"
#include "CLI/CmdDatabase.h"
#include "CLI/CmdAnalyze.h"

namespace grb
{

CommandFactoryType::CommandFactoryType()
{
}

Cmd*
CommandFactoryType::create(CommandLine& cli, const std::string& command)
{
  type::CommandType cmdType;
  try
  {
    cmdType = CommandMapper::instance()->getValue(command);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(cli, cmdType);
}

Cmd*
CommandFactoryType::create(CommandLine& cli, const type::CommandType cmdType)
{
  switch (cmdType)
  {
    case type::CMD_EXIT:
      return new CmdQuit(cli, type::CMD_EXIT);
    case type::CMD_QUIT:
      return new CmdQuit(cli);
    case type::CMD_HELP:
      return new CmdHelp(cli);
    case type::CMD_DATABASE:
      return new CmdDatabase(cli);
    case type::CMD_ANALYZE:
      return new CmdAnalyze(cli);
    default:
      break;
  }
  return nullptr;
}

}
