#include "CLI/CmdAnalyze.h"

#include <sstream>

#include "Common/trace.h"

namespace grb
{

namespace
{

const char* HELP_SHORT = " - performs correlation analysis.";
const char* HELP_LONG = " <SUB_COMMAND>";

}

CmdAnalyze::CmdAnalyze(CommandLine& cli)
  : Cmd(cli, type::CMD_ANALYZE)
{

}

bool
CmdAnalyze::parse(std::list<std::string>& args) throw(Exception)
{
  if (args.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  _subcommand = args.front();
  args.pop_front();

  return Cmd::parse(args);
}

std::string
CmdAnalyze::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

void
CmdAnalyze::doExecute(Analyzer*& analyzer)
{
  if (!analyzer)
  {
    std::stringstream ss;
    ss << "Noting to analyse. Provide a databse first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  analyzer->execute(_subcommand);
}

}
