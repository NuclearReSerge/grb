#include "Data/Catalog.h"
#include "Data/CatalogEntry.h"

namespace grb
{

Catalog::Catalog(type::CatalogEntryType type)
  : _type(type)
{
}

Catalog::~Catalog()
{
  for(CatalogEntry* entry : _catalog)
  {
    delete entry;
  }
  _catalog.clear();
}

type::CatalogEntryType
Catalog::getType() const
{
  return _type;
}

std::vector<CatalogEntry*>&
Catalog::getEntries()
{
  return _catalog;
}

}
