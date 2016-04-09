#include "Data/CatalogEntryFactory.h"
#include "Data/CatalogEntryGrbcat.h"

#include "test/CatalogEntryMock.h"

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
    case type::CATALOG_TEST:
      return new test::CatalogEntryMock;
    default:
      break;
  }
  return nullptr;
}

}
