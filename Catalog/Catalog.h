#pragma once

#include "Catalog/CatalogEntry.h"
#include "Catalog/CatalogType.h"

#include <vector>

namespace grb
{

class Catalog
{
public:
  Catalog(const type::CatalogType& type = type::UNDEFINED_CATALOG)
    : _type(type)
  {
  }

  virtual ~Catalog()
  {
    clear();
  }

  type::CatalogType getType() const
  {
    return _type;
  }

  std::vector<CatalogEntry*>& getEntries()
  {
    return _catalog;
  }

  const std::vector<CatalogEntry*>& getEntries() const
  {
    return _catalog;
  }

  bool empty() const
  {
    return _catalog.empty();
  }

  void clear()
  {
    for(CatalogEntry* entry : _catalog)
    {
      delete entry;
    }
    _catalog.clear();
  }

  virtual CatalogEntry* createEntry();

private:
  std::vector<CatalogEntry*> _catalog;
  type::CatalogType _type;

};

} // namespace grb
