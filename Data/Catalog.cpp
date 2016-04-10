#include "Data/Catalog.h"
#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryFactory.h"

namespace grb
{

Catalog::Catalog(type::CatalogType type)
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

type::CatalogType
Catalog::getType() const
{
  return _type;
}

bool
Catalog::isEmpty() const
{
  return _catalog.empty();
}

CatalogEntry*
Catalog::createEntry()
{
  return CatalogEntryFactory::instance()->create(_type);
}

void
Catalog::addEntry(CatalogEntry* entry)
{
  if (entry)
    _catalog.push_back(entry);
}

std::vector<CatalogEntry*>& Catalog::get()
{
  return _catalog;
}

}
