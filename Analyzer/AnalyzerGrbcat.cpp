#include "Analyzer/AnalyzerGrbcat.h"

#include "Analyzer/AnalyzerCmdMapper.h"
#include "Correlation/CorrelationFactory.h"
#include "Common/Exception.h"
#include "Data/Catalog.h"
#include "Main/AnalysisData.h"

#include <sstream>

namespace grb
{

AnalyzerGrbcat::AnalyzerGrbcat()
  : Analyzer(type::GRBCAT_ANALYZER), _corrType(grb::type::UNDEFINED_CORRELATION),
    _filePrefix("grbcf")
{
}

bool
AnalyzerGrbcat::doParse(std::list<std::string>& tokens)
{
  switch (getCmdType())
  {
    case type::AC_CREATE:
    {
      return parseCreate(tokens);
    }
    case type::AC_SET:
    {
      return parseSet(tokens);
    }
    case type::AC_BUILD:
    {
      return parseBuild();
    }
    case type::AC_SAVE:
    {
      if (!tokens.empty())
      {
        _filePrefix = tokens.front();
        tokens.pop_front();
      }
      return true;
    }
    default:
      break;
  }

  std::stringstream ss;
  ss << "AnalyzerGrbcat failed at parsing. Command '"
     << AnalyzerCmdMapper::instance()->getKey(getCmdType())
     << "' unhandled." << std::endl;
  Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                ss.str());
  throw exc;
}

void
AnalyzerGrbcat::doExecute()
{
  switch (getCmdType())
  {
    case type::AC_CREATE:
    {
      executeCreate();
      break;
    }
    case type::AC_SET:
    {
      executeSet();
      break;
    }
    case type::AC_BUILD:
    {
      executeBuild();
      break;
    }
    case type::AC_SAVE:
    {
      executeSave();
      break;
    }
    default:
      break;
  }
}

bool
AnalyzerGrbcat::parseCreate(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at parsing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. No arguments." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }

  std::string name = tokens.front();
  tokens.pop_front();

  try
  {
    _corrType = CorrelationMapper::instance()->getValue(name);
  }
  catch (Exception&)
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at parsing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. Correlation '"
       << name
       << "' unknown." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }
  return true;
}

void
AnalyzerGrbcat::executeCreate()
{
  Correlation* corr = CorrelationFactory::instance()->createType(_corrType);
  if (!corr)
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at executing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. Correlation '"
       << CorrelationMapper::instance()->getKey(_corrType)
       << "' not created." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }
  AnalysisData::instance()->setCorrelation(corr);
}

bool
AnalyzerGrbcat::parseSet(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at parsing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. No arguments." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }

  checkAnalyzerDataIsValid();

  return AnalysisData::instance()->getCorrelation()->parse(tokens);
}

void
AnalyzerGrbcat::executeSet()
{
  setConfigured();
}

bool
AnalyzerGrbcat::parseBuild()
{
  checkAnalyzerDataIsValid();

  if (!isConfigured())
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at parsing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. Correlation '"
       << CorrelationMapper::instance()->getKey(_corrType)
       << "' not configured." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }

  return true;
}

void
AnalyzerGrbcat::executeBuild()
{
  if (!AnalysisData::instance()->getCorrelation()->build(
        *AnalysisData::instance()->getCatalogData(),
        *AnalysisData::instance()->getCatalogModel()))
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at executing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. Correlation '"
       << CorrelationMapper::instance()->getKey(_corrType)
       << "' build failed." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }
}

void
AnalyzerGrbcat::executeSave()
{
  if (!AnalysisData::instance()->getCorrelation()->save(_filePrefix))
  {
    std::stringstream ss;
    ss << "AnalyzerGrbcat failed at executing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'. Correlation '"
       << CorrelationMapper::instance()->getKey(_corrType)
       << "' save failed." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }
}

void
AnalyzerGrbcat::checkAnalyzerDataIsValid()
{
  const Catalog* catalogData = AnalysisData::instance()->getCatalogData();
  const Catalog* catalogModel = AnalysisData::instance()->getCatalogModel();
  const Correlation* correlation = AnalysisData::instance()->getCorrelation();

  if (catalogData->getType() == type::GRBCAT_ENTRY &&
      catalogModel->getType() == type::GRBCAT_ENTRY &&
      correlation->getType() == type::CORRELATION_GRBCAT_DTDARC)
  {
    return;
  }

  std::stringstream ss;
  ss << "AnalyzerGrbcat input verification failure. ";

  if (catalogData->getType() != type::GRBCAT_ENTRY ||
           catalogModel->getType() != type::GRBCAT_ENTRY ||
           correlation->getType() != type::CORRELATION_GRBCAT_DTDARC)
  {
    ss << "Wrong type of { "
       << (catalogData->getType() == type::GRBCAT_ENTRY ? "" : "database ")
       << (catalogModel->getType() == type::GRBCAT_ENTRY ? "" : "model ")
       << (correlation->getType() == type::CORRELATION_GRBCAT_DTDARC ? "" : "correlation ")
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

} // namespace grb
