#include "Analyzer/AnalyzeGrbcat.h"
#include "Analyzer/CorrelationTimeArcGrbcat.h"
#include "Common/Exception.h"

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
  // todo subcommand
  if (subcommand.empty())
    return;

  _correlation = new CorrelationTimeArcGrbcat;

  if (!_correlation->buildCF(*getCatalog()))
  {
    Exception exc(type::EXCEPTION_CRITICAL, "Failed to build CF.", PRETTY_FUNCTION);
    throw exc;
  }
}

}
