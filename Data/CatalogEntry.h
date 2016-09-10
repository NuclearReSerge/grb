#include "Common/Global.h"
#include "Data/CatalogEntryType.h"
#include "Data/DataBaseColumn.h"

#pragma once

namespace grb
{

namespace mapper
{

class NameMapper;

}

class CatalogEntry
{
public:
  CatalogEntry(type::CatalogEntryType type = type::UNDEFINED_CATALOG_ENTRY)
    : _type(type)
  {
  }

  virtual ~CatalogEntry() = default;

  type::CatalogEntryType getType() const
  {
    return _type;
  }

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

  virtual mapper::NameMapper* getMapper(type::ColumnType column) = 0;

  virtual void setUnitType(type::ColumnType column, type::UnitType unitType) = 0;

  virtual bool isValid() = 0;

private:
  type::CatalogEntryType _type;
};

} // namespace grb
