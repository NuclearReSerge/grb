#include "Data/CatalogEntryMapper.h"
#include <vector>

#pragma once

namespace grb
{

class CatalogEntry;

class Catalog
{
public:
  Catalog(type::CatalogEntryType type = type::UNDEFINED_CATALOG_ENTRY);
  ~Catalog();

  type::CatalogEntryType getType() const;
  std::vector<CatalogEntry*>& getEntries();
protected:

  std::vector<CatalogEntry*> _catalog;

private:
  type::CatalogEntryType _type;

};

}
