#include "Data/CatalogEntry.h"

#include "Data/Catalog.h"

namespace grb
{

CatalogEntry::CatalogEntry(const Catalog& catalog)
  : _catalog(catalog)
{
}

CatalogEntry::~CatalogEntry()
{
}

type::CatalogType
CatalogEntry::getType() const
{
  return _catalog.getType();
}

}
