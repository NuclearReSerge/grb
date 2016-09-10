#include "Data/CatalogEntryFactory.h"

#include "Data/CatalogEntryGrbcat.h"

namespace grb
{
namespace factory
{

CatalogEntry*
CatalogEntryFactory::createType(const type::CatalogEntryType& type)
{
  switch (type)
  {
    case type::GRBCAT_ENTRY:
      return new CatalogEntryGrbcat;
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
