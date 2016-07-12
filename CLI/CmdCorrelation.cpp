#include "CLI/CmdCorrelation.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "generates correlation function.";
const char* HELP_LONG = "<SUB_COMMAND>";

}

CmdCorrelation::CmdCorrelation(CommandLine& cli)
  : Cmd(cli, type::CMD_CORRELATION)
{
}

bool
CmdCorrelation::doParse(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdCorrelation::doExecute()
{
}

std::string
CmdCorrelation::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}
}
