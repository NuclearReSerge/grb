#include "CLI/CmdQuit.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace
{

const char* HELP_SHORT = "exits/quits the program.";
const char* HELP_LONG = "";

} // namespace

namespace grb
{

CmdQuit::CmdQuit(type::CommandType cmdType)
  : Cmd(cmdType)
{
}

bool
CmdQuit::doParse(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdQuit::doExecute()
{
  if(getCLI())
    getCLI()->setQuit();
  std::cout << "Bye!" << std::endl;
}

std::string
CmdQuit::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

} // namespace grb
