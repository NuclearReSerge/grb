#include "Analyzer/AnalyzerGrbcat.h"
#include "Analyzer/CorrelationFactory.h"
#include "Analyzer/CorrelationTimeArcGrbcat.h"
#include "CLI/CommandLine.h"
#include "Common/Exception.h"
#include "Common/GlobalName.h"
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
  return static_cast<CatalogEntryGRBCAT*>(entry)->getTime().getTimeMJD();
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
{
}

AnalyzerGrbcat::~AnalyzerGrbcat()
{
}

bool
AnalyzerGrbcat::parse(std::list<std::string>& subcmd)
{
  while (!subcmd.empty())
  {
    bool result = false;
    std::string token = subcmd.front();
    subcmd.pop_front();

    if (token == SUB_CMD[subcmd::CREATE])
    {
      if (!subcmd.empty())
      {
        result = cmdCreate(subcmd.front());
        subcmd.pop_front();
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
      Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    if (!result)
    {
      std::stringstream ss;
      ss << "AnalyzerGrbcat failed at subcommand '" << token << "'" << std::endl;
      Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
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
  type::CorrelationType corrType = type::CORRELATION_TYPE_UNDEFINED;

  for (int i = 0; i < type::CORRELATION_TYPE_UNDEFINED; ++i)
  {
    if (cfName == GlobalName::getCorrelation((type::CorrelationType) i))
      corrType = (type::CorrelationType) i;
  }
  Correlation* correlation = CorrelationFactory::instance()->create(corrType);

  return correlation != nullptr;
}

bool
AnalyzerGrbcat::cmdSet()
{
  Catalog* catalog = G_CatalogData().get();
  auto minEntry = std::min_element(catalog->begin(), catalog->end(), CompareTime());
  auto maxEntry = std::max_element(catalog->begin(), catalog->end(), CompareTime());

  type::Float range = std::ceil((getTime(*maxEntry) - getTime(*minEntry)) / 365.0) * 365.0;

  Correlation* correlation = G_Correlation().get();
  correlation->setXAxis(range, 365);
  correlation->setYAxis(M_PIl, 180);

  return true;
}

bool
AnalyzerGrbcat::cmdBuild()
{
  Correlation* correlation = G_Correlation().get();
  if (!correlation->buildCF(*G_CatalogModel().get()))
  {
    Exception exc(type::EXCEPTION_CRITICAL, "Failed to build CF.", PRETTY_FUNCTION);
    throw exc;
  }

  return true;
}

bool
AnalyzerGrbcat::cmdSave()
{
  G_Correlation().get()->saveCF("grbcf");

  return true;
}

}
