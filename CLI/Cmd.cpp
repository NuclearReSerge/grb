#include "CLI/Cmd.h"
#include "CLI/CommandLine.h"
#include "CLI/CommandMapper.h"

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
Cmd::parse(std::list<std::string>& args) throw(Exception)
{
  doParse(args);
  if (!args.empty())
  {
    std::stringstream ss;
    ss << "Command " << CommandMapper::instance()->getKey(_type)
       << " has "<< args.size() << " unparsed arguments ";
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
Cmd::execute()
{
  doExecute();
  getCLI().incCmdIdx();
  _wasExecuted = true;
}

std::string
Cmd::help(type::HelpType type)
{
  std::string cmdName = CommandMapper::instance()->getKey(_type);
  std::stringstream ss;

  if (type == type::HELP_SHORT || type == type::HELP_FULL)
  {
    ss << cmdName << doHelp(type::HELP_SHORT) << std::endl;
  }
  if (type == type::HELP_LONG || type == type::HELP_FULL)
  {
    ss << "Usage: " << cmdName << doHelp(type::HELP_LONG) << std::endl;
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
