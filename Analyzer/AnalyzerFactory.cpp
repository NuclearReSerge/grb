#include "Analyzer/AnalyzerFactory.h"

#include "Analyzer/AnalyzerGrbcat.h"

namespace grb
{
namespace factory
{

Analyzer*
AnalyzerFactory::createType(const type::AnalyzerType& type)
{
  switch (type)
  {
    case type::GRBCAT_ANALYZER:
      return new AnalyzerGrbcat;
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
