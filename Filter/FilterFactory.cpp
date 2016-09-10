#include "Filter/FilterFactory.h"

#include "Filter/FilterNone.h"

namespace grb
{
namespace factory
{

Filter*
FilterFactory::createType(const type::FilterType& type)
{
  switch (type)
  {
    case type::FILTER_NONE:
      return new FilterNone;
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
