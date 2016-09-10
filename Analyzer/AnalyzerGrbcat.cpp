#include "Analyzer/AnalyzerGrbcat.h"

#include "Correlation/CorrelationFactory.h"
#include "Correlation/CorrelationTimeArcGrbcat.h"
#include "CLI/CommandLine.h"
#include "Common/Exception.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"
#include "Main/AnalysisData.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

namespace grb
{

namespace subcmd
{
enum SubCmd
{
  CREATE,
  SET,
  BUILD,
  SAVE,
  // LAST
  SUB_CMD_UNDEFINED
};
}

namespace
{
std::vector<std::string> SUB_CMD
{
  "create",
  "set",
  "build",
  "save",
  // LAST
  "undefined sub command"
};

type::Float getTime(CatalogEntry* entry)
{
  return static_cast<CatalogEntryGrbcat*>(entry)->getCoodinates().getTimeMJD();
}

class CompareTime
{
public:
  bool operator()(CatalogEntry* a, CatalogEntry* b)
  {
    return getTime(a) < getTime(b);
  }
};

}

AnalyzerGrbcat::AnalyzerGrbcat()
  : Analyzer(type::GRBCAT_ANALYZER), _correlation(nullptr)
{
}

AnalyzerGrbcat::~AnalyzerGrbcat()
{
  delete _correlation;
}

bool
AnalyzerGrbcat::parse(std::list<std::string>& tokens)
{
  while (!tokens.empty())
  {
    bool result = false;
    std::string token = tokens.front();
    tokens.pop_front();

    if (token == SUB_CMD[subcmd::CREATE])
    {
      if (!tokens.empty())
      {
        result = cmdCreate(tokens.front());
        tokens.pop_front();
      }
    }
    else if (token == SUB_CMD[subcmd::SET])
    {
      result = cmdSet();
    }
    else if (token == SUB_CMD[subcmd::BUILD])
    {
      result = cmdBuild();
    }
    else if (token == SUB_CMD[subcmd::SAVE])
    {
      result = cmdSave();
    }
    else
    {
      std::stringstream ss;
      ss << "Unknown subcommand '"<< token <<"' passed to AnalyzerGrbcat." << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str().c_str(), PRETTY_FUNCTION);
      throw exc;
    }

    if (!result)
    {
      std::stringstream ss;
      ss << "AnalyzerGrbcat failed at subcommand '" << token << "'" << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str().c_str(), PRETTY_FUNCTION);
      throw exc;
    }
  }
  return true;
}

void
AnalyzerGrbcat::run()
{

}

bool
AnalyzerGrbcat::cmdCreate(std::string& cfName)
{
  _correlation = CorrelationFactory::instance()->createName(cfName);
  return _correlation != nullptr;
}

bool
AnalyzerGrbcat::cmdSet()
{
  Catalog* catalog = G_CatalogData().get();
  auto minEntry = std::min_element(catalog->getEntries().begin(), catalog->getEntries().end(),
                                   CompareTime());
  auto maxEntry = std::max_element(catalog->getEntries().begin(), catalog->getEntries().end(),
                                   CompareTime());

  type::Float range = std::ceil((getTime(*maxEntry) - getTime(*minEntry)) / 365.0) * 365.0;

  _correlation->setXAxis(range, 365);
  _correlation->setYAxis(M_PIl, 180);

  return true;
}

bool
AnalyzerGrbcat::cmdBuild()
{
  if (!_correlation->buildCF(*G_CatalogData().get(),
                             *G_CatalogModel().get()))
  {
    Exception exc(type::EXCEPTION_CRITICAL, "Failed to build CF.", PRETTY_FUNCTION);
    throw exc;
  }

  return true;
}

bool
AnalyzerGrbcat::cmdSave()
{
  _correlation->saveCF("grbcf");

  return true;
}

}
