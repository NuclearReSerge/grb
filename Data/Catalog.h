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
  std::vector<CatalogEntry*>::const_iterator begin() const;
  std::vector<CatalogEntry*>::const_iterator end() const;
  const CatalogEntry& operator[](std::size_t index) const;

protected:
  friend class Parser;
  virtual CatalogEntry* createEntry();
  void addEntry(CatalogEntry* entry);

  void setUnitType(type::ColumnType column, type::UnitType unitType);

private:
  type::CatalogType _type;
  std::map<type::ColumnType, type::UnitType> _unitMap;

  std::vector<CatalogEntry*> _catalog;

};

}
