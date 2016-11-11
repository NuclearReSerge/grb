#include "Analyzer/AnalyzerGrbcat.h"

#include "Analyzer/AnalyzerCmdMapper.h"
#include "Catalog/Catalog.h"
#include "Correlation/CorrelationFactory.h"
#include "Common/Exception.h"
#include "Main/AnalysisData.h"

#include <sstream>

namespace grb
{

AnalyzerGrbcat::AnalyzerGrbcat()
  : Analyzer(type::GRBCAT_ANALYZER)
{
}

bool
AnalyzerGrbcat::isConfigurationValid()
{
  const Catalog* catalogData = AnalysisData::instance()->getCatalogData();
  const Catalog* catalogModel = AnalysisData::instance()->getCatalogModel();
  const Correlation* correlation = AnalysisData::instance()->getCorrelation();
  const Model* model = AnalysisData::instance()->getModel();
  const Filter* filter = AnalysisData::instance()->getFilter();

  if (!catalogData || !catalogModel || !correlation || !model || !filter)
    return false;

  if (catalogData->getType() == type::GRBCAT &&
      catalogModel->getType() == type::GRBCAT &&
      correlation->getType() == type::CORRELATION_GRBCAT_DTDARC)
    return true;

  std::stringstream ss;
  ss << "AnalyzerGrbcat input verification failure. ";

  if (catalogData->getType() != type::GRBCAT ||
      catalogModel->getType() != type::GRBCAT ||
      correlation->getType() != type::CORRELATION_GRBCAT_DTDARC)
  {
    ss << "Wrong type of { "
       << (catalogData->getType() == type::GRBCAT ? "" : "database ")
       << (catalogModel->getType() == type::GRBCAT ? "" : "model ")
       << (correlation->getType() == type::CORRELATION_GRBCAT_DTDARC ? "" : "correlation ")
       << "}";
  }

  ss << std::endl;

  Exception exc(type::EXCEPTION_CRITICAL + type::EXCEPTION_MOD_NO_PREFIX,
                ss.str());
  throw exc;
}

bool
AnalyzerGrbcat::doParse(type::AnalyzerCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    default:
      break;
  }

  tokens.clear();

  std::stringstream ss;
  ss << "AnalyzerGrbcat failed at parsing. Command '"
     << AnalyzerCmdMapper::instance()->getKey(cmd)
     << "' unhandled." << std::endl;
  Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                ss.str());
  throw exc;
}

void
AnalyzerGrbcat::doExecute(type::AnalyzerCmdType cmd)
{
  switch (cmd)
  {
    default:
      break;
  }
}

std::string
AnalyzerGrbcat::doList()
{
  return "AnalyzerGrbcat::doList";
}

std::string
AnalyzerGrbcat::doHelp()
{
  return "AnalyzerGrbcat::doHelp";
}

} // namespace grb
