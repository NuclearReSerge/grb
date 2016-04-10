#include "Data/CatalogEntryFactory.h"
#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

CatalogEntryFactoryType::CatalogEntryFactoryType()
{
}

CatalogEntry*
CatalogEntryFactoryType::create(type::CatalogType catType)
{
  switch (catType)
  {
    case type::GRBCAT:
      return new CatalogEntryGRBCAT;
    default:
      break;
  }
  return nullptr;
}

}
