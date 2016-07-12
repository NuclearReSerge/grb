#include "CLI/CmdHelp.h"
#include "CLI/CmdFactory.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "list of all available commands or specific help for a given command.";
const char* HELP_LONG = "[<COMMAND>]\n"
"\n"
"    COMMAND : existing command name";

}

CmdHelp::CmdHelp(CommandLine& cli)
  : Cmd(cli, type::CMD_HELP), _showAll(true)
{
}

bool
CmdHelp::doParse(std::list<std::string>& tokens)
{ 
  if (!tokens.empty())
  {
    _specific = tokens.front();
    _showAll = false;
    tokens.pop_front();
  }
  return true;
}

void
CmdHelp::doExecute()
{
  if (_showAll)
  {
    std::cout << "Available commands:" << std::endl;
    for (int i = 0; i < type::UNDEFINED_COMMAND; ++i)
    {
      Cmd* cmd = CmdFactory::instance()->create(getCLI(), (type::CommandType) i);
      if (!cmd)
      {
        std::cout << "No help for command "
                  << CmdMapper::instance()->getKey((type::CommandType) i) << std::endl;
        return;
      }
      std::cout << cmd->help(type::HELP_SHORT);
      delete cmd;
    }
  }
  else
  {
    Cmd* cmd = CmdFactory::instance()->create(getCLI(), _specific);
    if (!cmd)
    {
      std::cout << "No help for command " << _specific << " or wrong command name." << std::endl;
      return;
    }
    std::cout << cmd->help(type::HELP_FULL);
    delete cmd;
  }
  std::cout << std::endl;
}

std::string
CmdHelp::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

}
