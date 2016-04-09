#include "Data/CatalogEntry.h"

#include <vector>

#pragma once

namespace grb
{

class Catalog
{
public:
  Catalog(type::CatalogType type = type::CATALOG_TYPE_UNDEFINED)
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

  type::CatalogType getType()
  {
    return _type;
  }

  std::vector<CatalogEntry*>& get()
  {
    return _catalog;
  }

protected:

private:
  type::CatalogType _type;
  std::vector<CatalogEntry*> _catalog;
};

}
