#include "Common/Global.h"

#pragma once

namespace grb
{

class Catalog;
class NameMapper;

class CatalogEntry
{
public:
  CatalogEntry() = delete;
  CatalogEntry(const Catalog& catalog);
  virtual ~CatalogEntry();

  type::CatalogType getType() const;

protected:
  friend class Parser;
  virtual type::Flag* getFlag(type::ColumnType column) = 0;
  virtual type::Integer* getInteger(type::ColumnType column) = 0;
  virtual type::Index* getIndex(type::ColumnType column) = 0;
  virtual type::IntegerRange* getIntegerRange(type::ColumnType column) = 0;
  virtual type::IndexList* getIndexList(type::ColumnType column) = 0;
  virtual type::Float* getFloat(type::ColumnType column) = 0;
  virtual type::String* getString(type::ColumnType column) = 0;
  virtual type::StringList* getStringList(type::ColumnType column) = 0;

  virtual NameMapper* getMapper(type::ColumnType column) = 0;

  virtual void setUnitType(type::ColumnType column, type::UnitType unitType) = 0;

  virtual bool isValid() = 0;

private:
  const Catalog& _catalog;
};

}
