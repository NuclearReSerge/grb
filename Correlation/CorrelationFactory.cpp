#include "Correlation/CorrelationFactory.h"

#include "Correlation/CorrelationTimeArcGrbcat.h"

namespace grb
{

namespace factory
{

Correlation*
CorrelationFactory::create(type::CorrelationType type)
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

Correlation*
CorrelationFactory::create(const std::string& name)
{
  type::CorrelationType type;
  try
  {
    type = CorrelationMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(type);
}

}

}
