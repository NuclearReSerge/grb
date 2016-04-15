#include "Data/CatalogEntryFactory.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

CatalogEntryFactoryType::CatalogEntryFactoryType()
{
}

CatalogEntry*
CatalogEntryFactoryType::create(const Catalog& catalog)
{
  switch (catalog.getType())
  {
    case type::GRBCAT:
      return new CatalogEntryGRBCAT(catalog);
    default:
      break;
  }
  return nullptr;
}

}
