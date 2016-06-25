#include "Analyzer/AnalyzerFactory.h"
#include "Analyzer/AnalyzerGrbcat.h"

namespace grb
{

AnalyzerFactoryType::AnalyzerFactoryType()
{
}

Analyzer*
AnalyzerFactoryType::create(type::CatalogType catType)
{
  switch (catType)
  {
    case type::GRBCAT:
      return new AnalyzerGrbcat;
    default:
      break;
  }
  return nullptr;
}


}
