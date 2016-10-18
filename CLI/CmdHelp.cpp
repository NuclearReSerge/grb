#include "CLI/CmdHelp.h"

#include "CLI/CommandFactory.h"
#include "CLI/CommandMapper.h"
#include "CLI/CommandLine.h"

#include <iostream>

namespace
{

const char* HELP_SHORT = "list of all available commands or specific help for a given command.";
const char* HELP_LONG = "[<COMMAND>]\n"
"\n"
"    COMMAND : existing command name\n"
"\n"
"Available commands:\n";

} // namespace

namespace grb
{

CmdHelp::CmdHelp()
  : Cmd(type::CMD_HELP), _showAll(true)
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
      Cmd* cmd = CommandFactory::instance()->createType((type::CommandType) i);
      if (!cmd)
      {
        std::cout << "# '"
                  << CommandMapper::instance()->getKey((type::CommandType) i)
                  << "' - command unavailable." << std::endl;
        continue;
      }
      std::cout << cmd->help(type::HELP_SHORT);
      delete cmd;
    }
  }
  else
  {
    Cmd* cmd = CommandFactory::instance()->createName(_specific);
    if (!cmd)
    {
      std::cout << "No help for command '" << _specific << "', wrong command name." << std::endl;
      return;
    }
    std::cout << cmd->help(type::HELP_FULL);
    delete cmd;
  }
  std::cout << std::endl;
}

std::string
CmdHelp::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_COMMAND; ++i)
  {
    ss << "  "
       << CommandMapper::instance()->getKey((type::CommandType) i)
       << std::endl;
  }

  return ss.str();
}

} // namespace grb
