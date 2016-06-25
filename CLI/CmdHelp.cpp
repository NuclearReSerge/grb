#include "CLI/CmdHelp.h"
#include "CLI/CommandFactory.h"
#include "CLI/CommandLine.h"
#include "CLI/CommandMapper.h"

#include <iostream>

namespace grb
{

namespace
{

const char* HELP_SHORT = " - this help";
const char* HELP_LONG = " [COMMAND] - specific help for a given COMMAND\n"
                        "  COMMAND : existing command name"
                        "";

}

CmdHelp::CmdHelp(CommandLine& cli)
  : Cmd(cli, type::CMD_HELP), _showAll(true)
{
}

bool
CmdHelp::doParse(std::list<std::string>& args)
{ 
  if (!args.empty())
  {
    _specific = args.front();
    _showAll = false;
    args.pop_front();
  }

  if (!args.empty())
  {
    std::stringstream ss;
    ss << "Command " << CommandMapper::instance()->getKey(getType()) << " ";
    for (std::string arg : args)
    {
      ss << arg << " ";
    }
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  return true;
}

void
CmdHelp::doExecute()
{
  std::cout << "Available commands:" << std::endl;

  if (_showAll)
  {
    for (int i = 0; i < type::COMMAND_UNDEFINED; ++i)
    {
      Cmd* cmd = CommandFactory::instance()->create(getCLI(), (type::CommandType) i);
      if (!cmd)
      {
        std::cout << "No help for command "
                  << CommandMapper::instance()->getKey((type::CommandType) i) << std::endl;
        return;
      }
      std::cout << cmd->help(type::HELP_SHORT);
      delete cmd;
    }
  }
  else
  {
    Cmd* cmd = CommandFactory::instance()->create(getCLI(), _specific);
    if (!cmd)
    {
      std::cout << "No help for command " << _specific << " or wrong command name." << std::endl;
      return;
    }
    std::cout << cmd->help(type::HELP_FULL);
    delete cmd;
  }
}

std::string
CmdHelp::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

}
