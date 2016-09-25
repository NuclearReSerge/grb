#include "CLI/CmdAnalyzer.h"

#include "Analyzer/AnalyzerFactory.h"
#include "Main/AnalysisData.h"

#include <sstream>

namespace
{

const char* HELP_SHORT = "performs correlation analysis.";
const char* HELP_LONG = "<SUB_COMMAND>";

} // namespace

namespace grb
{

CmdAnalyzer::CmdAnalyzer()
  : Cmd(type::CMD_ANALYZER)
{
}

bool
CmdAnalyzer::doParse(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getAnalyzer())
  {
    if (!AnalysisData::instance()->getCatalogData())
    {
      std::stringstream ss;
      ss << "Noting to analyse. Provide a databse first.";
      Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    Analyzer* analyzer = createAnalyzer("grbcat-analyzer" /*parse this*/);
    if (!analyzer)
    {
      std::stringstream ss;
      ss << "Analyzer not available." << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
    AnalysisData::instance()->setAnalyzer(analyzer);
  }
  return AnalysisData::instance()->getAnalyzer()->parse(tokens);
}

void
CmdAnalyzer::doExecute()
{
  if (!AnalysisData::instance()->getAnalyzer()->isConfigured())
    return;

  if (!AnalysisData::instance()->getCatalogModel())
  {
    std::stringstream ss;
    ss << "Noting to analyse. Provide a model first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->getAnalyzer()->execute();
}

std::string
CmdAnalyzer::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

Analyzer*
CmdAnalyzer::createAnalyzer(const std::string& name)
{
  return AnalyzerFactory::instance()->createName(name);
}

/*
void
Analyzer::checkAnalyzerDataIsValid()
{
  const Catalog* catalogData = AnalysisData::instance()->getCatalogData();
  const Catalog* catalogModel = AnalysisData::instance()->getCatalogModel();
  const Correlation* correlation = AnalysisData::instance()->getCorrelation();

  if (catalogData && !catalogData->empty() && catalogModel && !catalogModel->empty() &&
      correlation)
  {
    return;
  }

  std::stringstream ss;
  ss << "Analyzer input verification failure. ";

  if (!catalogData || !catalogModel || !correlation)
  {
    ss << "Uncreated { "
       << (catalogData ? "" : "datatabase ")
       << (catalogModel ? "" : "model ")
       << (correlation ? "" : "correlation ")
       << "}";
  }
  else if (catalogData->empty() || catalogModel->empty())
  {
    ss << "Empty { "
       << (catalogData->empty() ? "database " : "")
       << (catalogModel->empty() ? "model " : "")
       << "}";
  }
  else
  {
    ss << "Unspecified.";
  }

  ss << std::endl;
  Exception exc(type::EXCEPTION_CRITICAL + type::EXCEPTION_MOD_NO_PREFIX,
                ss.str());
  throw exc;
}
 */


} // namespace grb
