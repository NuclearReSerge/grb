#include "Analyzer/AnalyzerFactory.h"
#include "CLI/CmdAnalyze.h"
#include "Main/AnalysisData.h"

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
CmdAnalyze::doParse(std::list<std::string>& args)
{
  if (args.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  if (!G_Analyzer().get())
  {
    if (!G_CatalogData().get())
    {
      std::stringstream ss;
      ss << "Noting to analyse. Provide a databse first.";
      Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    Analyzer* analyzer = AnalyzerFactory::instance()->create(G_CatalogData().get()->getType());
    if (!analyzer)
    {
      std::stringstream ss;
      ss << "Analyzer not available." << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
    G_Analyzer().reset(analyzer);
  }
  return G_Analyzer().get()->parse(args);
}

void
CmdAnalyze::doExecute()
{
  G_Analyzer().get()->run();
}

std::string
CmdAnalyze::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

}
