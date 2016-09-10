#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryType.h"

#include <vector>

#pragma once

namespace grb
{

class Catalog
{
public:
  Catalog(type::CatalogEntryType type = type::UNDEFINED_CATALOG_ENTRY)
    : _type(type)
  {
  }

  ~Catalog()
  {
    for(CatalogEntry* entry : _catalog)
    {
      delete entry;
    }
    _catalog.clear();
  }

  type::CatalogEntryType getType() const
  {
    return _type;
  }

  std::vector<CatalogEntry*>& getEntries()
  {
    return _catalog;
  }

protected:
  std::vector<CatalogEntry*> _catalog;

private:
  type::CatalogEntryType _type;

};

} // namespace grb
