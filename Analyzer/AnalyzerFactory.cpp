#include "Analyzer/AnalyzerFactory.h"

#include "Analyzer/AnalyzeGrbcat.h"

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
      return new AnalyzeGrbcat;
    default:
      break;
  }
  return nullptr;
}


}
