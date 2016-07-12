#include "Analyzer/AnalyzerFactory.h"
#include "CLI/CmdAnalyzer.h"
#include "Main/AnalysisData.h"

#include <sstream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "performs correlation analysis.";
const char* HELP_LONG = "<SUB_COMMAND>";

}

CmdAnalyzer::CmdAnalyzer(CommandLine& cli)
  : Cmd(cli, type::CMD_ANALYZER)
{
}

bool
CmdAnalyzer::doParse(std::list<std::string>& tokens)
{
  if (tokens.empty())
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

    Analyzer* analyzer = AnalyzerFactory::instance()->create(type::GRBCAT_ANALYZER /*parse this*/);
    if (!analyzer)
    {
      std::stringstream ss;
      ss << "Analyzer not available." << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
    G_Analyzer().reset(analyzer);
  }
  return G_Analyzer().get()->parse(tokens);
}

void
CmdAnalyzer::doExecute()
{
  if (!G_Analyzer().get()->isConfigured())
    return;

  if (!G_CatalogModel().get())
  {
    std::stringstream ss;
    ss << "Noting to analyse. Provide a model first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  G_Analyzer().get()->run();
}

std::string
CmdAnalyzer::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

}
