#include "Common/Global.h"

#include <vector>

#pragma once

namespace grb
{

class CatalogEntry;

class Catalog
{
public:
  Catalog(type::CatalogType type = type::CATALOG_TYPE_UNDEFINED);
  virtual ~Catalog();

  type::CatalogType getType() const;
  bool isEmpty() const;

  virtual CatalogEntry* createEntry();
  void addEntry(CatalogEntry* entry);
  std::vector<CatalogEntry*>& get();

protected:
  type::CatalogType _type;
  std::vector<CatalogEntry*> _catalog;
};

}
