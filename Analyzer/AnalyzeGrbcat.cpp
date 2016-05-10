#include "Analyzer/AnalyzeGrbcat.h"
#include "Analyzer/CorrelationTimeArcGrbcat.h"
#include "CLI/CommandLine.h"
#include "Common/Exception.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

#include <algorithm>
#include <cmath>

namespace grb
{

AnalyzeGrbcat::AnalyzeGrbcat()
  : _correlation(nullptr)
{
}

AnalyzeGrbcat::~AnalyzeGrbcat()
{
  delete _correlation;
}

void
AnalyzeGrbcat::execute(const std::string& subcommand)
{
  if (subcommand.empty())
    return;

  CommandLine::tokenize(subcommand, _subcmd);

  parse();
}

void
AnalyzeGrbcat::parse()
{
  // TODO
  cmdCreateCF();
  cmdSetupCF();
  cmdBuildCF();
  cmdWriteCF();
}

void
AnalyzeGrbcat::cmdCreateCF()
{
  _correlation = new CorrelationTimeArcGrbcat;

}

namespace
{

type::Float getTime(const CatalogEntry* entry)
{
  return static_cast<const CatalogEntryGRBCAT*>(entry)->getTime().getTimeMJD();
}

class CompareTime
{
public:
  bool operator()(const CatalogEntry* a, const CatalogEntry* b)
  {
    return getTime(a) < getTime(b);
  }
};

}

void
AnalyzeGrbcat::cmdSetupCF()
{
  const auto minEntry = std::min_element(getCatalog()->begin(), getCatalog()->end(), CompareTime());
  const auto maxEntry = std::max_element(getCatalog()->begin(), getCatalog()->end(), CompareTime());

  type::Float range = std::ceil((getTime(*maxEntry) - getTime(*minEntry)) / 365.0) * 365.0;

  _correlation->setXAxis(range, 365);
  _correlation->setYAxis(M_PIl, 180);
}

void
AnalyzeGrbcat::cmdBuildCF()
{
  if (!_correlation->buildCF(*getCatalog()))
  {
    Exception exc(type::EXCEPTION_CRITICAL, "Failed to build CF.", PRETTY_FUNCTION);
    throw exc;
  }
}

void
AnalyzeGrbcat::cmdWriteCF()
{
  _correlation->saveCF("grbcf");
}

}
