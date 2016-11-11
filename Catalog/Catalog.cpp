#include "Catalog/Catalog.h"

#include "Catalog/CatalogEntryFactory.h"

namespace grb
{

CatalogEntry*
Catalog::createEntry()
{
  return CatalogEntryFactory::instance()->createType(_type);
}

} // namespace grb
