#include "CLI/CmdQuit.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "exits/quits the program.";
const char* HELP_LONG = "";

}

CmdQuit::CmdQuit(CommandLine& cli, type::CommandType cmdType)
  : Cmd(cli, cmdType)
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
  getCLI().setQuit();
  std::cout << "Bye!" << std::endl;
}

std::string
CmdQuit::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}
}
