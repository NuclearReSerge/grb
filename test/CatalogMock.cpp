#include "test/CatalogMock.h"

#include "test/CatalogEntryMock.h"

namespace grb
{
namespace test
{

CatalogMock::CatalogMock()
  : Catalog(type::CATALOG_TEST)
{
}

CatalogEntry*
CatalogMock::createEntry()
{
  return new CatalogEntryMock();
}

}
}
