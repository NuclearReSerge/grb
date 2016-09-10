#include "CLI/CmdFilter.h"

namespace
{

const char* HELP_SHORT = "filters catalog entries.";
const char* HELP_LONG = "<SUB_COMMAND>";

} // namespace

namespace grb
{

CmdFilter::CmdFilter()
  : Cmd(type::CMD_FILTER)
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
CmdFilter::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

} // namespace grb
