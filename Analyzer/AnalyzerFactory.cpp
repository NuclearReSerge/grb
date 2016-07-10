#include "Analyzer/AnalyzerFactory.h"

#include "Analyzer/AnalyzerGrbcat.h"

namespace grb
{

namespace factory
{

Analyzer*
AnalyzerFactory::create(type::AnalyzerType type)
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

Analyzer*
AnalyzerFactory::create(const std::string& name)
{
  type::AnalyzerType type;
  try
  {
    type = AnalyzerMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(type);
}

}

}
