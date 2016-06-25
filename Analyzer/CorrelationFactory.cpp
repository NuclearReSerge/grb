#include "Analyzer/CorrelationFactory.h"
#include "Analyzer/CorrelationTimeArcGrbcat.h"

namespace grb
{

CorrelationFactoryType::CorrelationFactoryType()
{
}

Correlation*
CorrelationFactoryType::create(type::CorrelationType corrType)
{
  switch (corrType)
  {
    case type::CORR_GRBCAT_TIME_DIFF_VS_CIRCLE_DIST:
      return new CorrelationTimeArcGrbcat;
    default:
      break;
  }
  return nullptr;
}

}
