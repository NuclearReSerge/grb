#include "CLI/CmdCorrelation.h"

namespace
{

const char* HELP_SHORT = "generates correlation function.";
const char* HELP_LONG = "<SUB_COMMAND>";

} // namespace

namespace grb
{

CmdCorrelation::CmdCorrelation()
  : Cmd(type::CMD_CORRELATION)
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
CmdCorrelation::doHelp(const type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

} // namespace grb
