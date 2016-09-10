#include "CLI/CommandFactory.h"

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
CommandFactory::createType(const type::CommandType& type)
{
  switch (type)
  {
    case type::CMD_EXIT:
      return new CmdQuit(type::CMD_EXIT);
    case type::CMD_QUIT:
      return new CmdQuit();
    case type::CMD_HELP:
      return new CmdHelp();
    case type::CMD_DATABASE:
      return new CmdDatabase();
    case type::CMD_MODEL:
      return new CmdModel();
    case type::CMD_FILTER:
      return new CmdFilter();
    case type::CMD_CORRELATION:
      return new CmdCorrelation();
    case type::CMD_ANALYZER:
      return new CmdAnalyzer();
    default:
      break;
  }
  return nullptr;
}

} //namespace factory
} //namespace grb
