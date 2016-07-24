#include "CLI/Cmd.h"
#include "CLI/CommandLine.h"

#include <sstream>

namespace grb
{

Cmd::Cmd(CommandLine& cli, type::CommandType cmdType)
  : _cli(cli), _type(cmdType), _wasExecuted(false)
{
}

Cmd::~Cmd()
{
}

type::CommandType
Cmd::getType() const
{
  return _type;
}

bool
Cmd::parse(std::list<std::string>& tokens) throw(Exception)
{
  doParse(tokens);
  if (!tokens.empty())
  {
    std::stringstream ss;
    ss << "Command " << CmdMapper::instance()->getKey(_type)
       << " has "<< tokens.size() << " unparsed argument(s) '";
    for (std::string arg : tokens)
    {
      ss << arg << " ";
    }
    ss << "'";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  return true;
}

void
Cmd::execute()
{
  doExecute();
  getCLI().incCmdIdx();
  _wasExecuted = true;
}

std::string
Cmd::help(type::HelpType type)
{
  std::string cmdName = CmdMapper::instance()->getKey(_type);
  std::stringstream ss;

  if (type == type::HELP_SHORT || type == type::HELP_FULL)
  {
    if (type == type::HELP_SHORT)
    {
      ss.width(CmdMapper::instance()->maxCmdLength() + 1);
    }
    else
    {
      ss << " ";
    }
    ss << cmdName << " - " << doHelp(type::HELP_SHORT) << std::endl;
  }
  if (type == type::HELP_LONG || type == type::HELP_FULL)
  {
    ss << std::endl
       << "Usage: " << std::endl
       << "  " << getCLI().getPrompt(false) << cmdName
       << " " << doHelp(type::HELP_LONG) << std::endl;
  }
  return ss.str();
}

bool
Cmd::wasExecuted() const
{
  return _wasExecuted;
}

CommandLine& Cmd::getCLI()
{
  return _cli;
}

}
