#include "Analyzer/Correlation.h"

namespace grb
{

Correlation::Correlation(type::CorrelationType type)
  : _type(type)
{

}

Correlation::~Correlation()
{

}

type::CorrelationType
Correlation::getType() const
{
  return _type;
}

}
