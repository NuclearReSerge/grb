#include "Correlation/CorrelationFactory.h"

#include "Correlation/CorrelationTimeArcGrbcat.h"

namespace grb
{
namespace factory
{

Correlation*
CorrelationFactory::createType(const type::CorrelationType& type)
{
  switch (type)
  {
    case type::CORRELATION_GRBCAT_DTDARC:
      return new CorrelationTimeArcGrbcat;
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
