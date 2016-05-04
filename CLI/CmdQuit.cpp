#include "CLI/CmdQuit.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = " - exits the program";
const char* HELP_LONG = "";

}

CmdQuit::CmdQuit(CommandLine& cli, type::CommandType cmdType)
  : Cmd(cli, cmdType)
{
}

bool
CmdQuit::parse(std::list<std::string>& args) throw(Exception)
{
  return Cmd::parse(args);
}

std::string
CmdQuit::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

void
CmdQuit::doExecute(Analyzer& analyzer)
{
  analyzer.getCatalog(); // dummy
  getCLI().setQuit();
  std::cout << "Bye!" << std::endl;
}

}
