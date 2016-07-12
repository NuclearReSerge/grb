#include "CLI/CmdFilter.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "filters catalog entries.";
const char* HELP_LONG = "<SUB_COMMAND>";

}

CmdFilter::CmdFilter(CommandLine& cli)
  : Cmd(cli, type::CMD_FILTER)
{
}

bool
CmdFilter::doParse(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdFilter::doExecute()
{
}

std::string
CmdFilter::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}
}
