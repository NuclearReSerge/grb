#include "Data/CatalogEntryFactory.h"

#include "Data/CatalogEntryGrbcat.h"

namespace grb
{
namespace factory
{

CatalogEntry*
CatalogEntryFactory::createType(const type::CatalogType& type)
{
  switch (type)
  {
    case type::GRBCAT:
      return new CatalogEntryGrbcat;
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
