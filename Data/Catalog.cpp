#include "Data/Catalog.h"

#include "Data/CatalogEntryFactory.h"

namespace grb
{

CatalogEntry*
Catalog::createEntry()
{
  return CatalogEntryFactory::instance()->createType(_type);
}

} // namespace grb
