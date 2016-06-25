#include "Common/Global.h"

#include <map>
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
  type::UnitType getUnitType(type::ColumnType column) const;

  bool empty() const;
  std::size_t size() const;

  std::vector<CatalogEntry*>::iterator begin();
  std::vector<CatalogEntry*>::iterator end();
  CatalogEntry& operator[](std::size_t index);


  virtual CatalogEntry* createEntry();
  void addEntry(CatalogEntry* entry);

protected:
  friend class Parser;
  void setUnitType(type::ColumnType column, type::UnitType unitType);

  std::vector<CatalogEntry*> _catalog;

private:
  type::CatalogType _type;
  std::map<type::ColumnType, type::UnitType> _unitMap;
};

}
