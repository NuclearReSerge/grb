#include "Common/Exception.h"
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
  std::size_t getSize() const;

  virtual CatalogEntry* createEntry();
  void addEntry(CatalogEntry* entry);
  const CatalogEntry& getEntry(std::size_t index) const throw(Exception);

protected:
  type::CatalogType _type;
  std::vector<CatalogEntry*> _catalog;
};

}
