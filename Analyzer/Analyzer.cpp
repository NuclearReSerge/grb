#include "Analyzer/Analyzer.h"

namespace grb
{

Analyzer::Analyzer(type::AnalyzerType type)
  : _type(type), _configured(false)
{
}

Analyzer::~Analyzer()
{
}

type::AnalyzerType
Analyzer::getType() const
{
  return _type;
}

bool
Analyzer::isConfigured() const
{
  return _configured;
}

void
Analyzer::setConfigured(const bool configured)
{
  _configured = configured;
}

}
