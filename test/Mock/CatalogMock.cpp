#include "test/Mock/CatalogMock.h"
#include "test/Mock/CatalogEntryMock.h"

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
  return new CatalogEntryMock(*this);
}

}
}
