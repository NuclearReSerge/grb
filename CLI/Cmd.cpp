#include "CLI/Cmd.h"
#include "CLI/CommandLine.h"
#include "CLI/CommandMapper.h"

#include <sstream>

namespace grb
{

bool
Cmd::parse(std::list<std::string>& tokens) throw(Exception)
{
  doParse(tokens);
  if (!tokens.empty())
  {
    std::stringstream ss;
    ss << "Command " << CommandMapper::instance()->getKey(_type)
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
  if (getCLI())
    getCLI()->incCmdIdx();
  _wasExecuted = true;
}

std::string
Cmd::help(type::CommandHelpType type)
{
  std::string cmdName = CommandMapper::instance()->getKey(_type);
  std::stringstream ss;

  if (type == type::HELP_SHORT || type == type::HELP_FULL)
  {
    if (type == type::HELP_SHORT)
    {
      ss.width(CommandHelper::maxCommandLength() + 1);
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
       << "  " << (getCLI() ? getCLI()->getPrompt(false) : "") << cmdName
       << " " << doHelp(type::HELP_LONG) << std::endl;
  }
  return ss.str();
}

} // namespace grb
