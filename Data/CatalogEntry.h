#include "Common/Global.h"
#include "Tools/NameMapper.h"

#include <string>
#include <vector>

#pragma once

namespace grb
{

class CatalogEntry
{
public:
  CatalogEntry() = delete;
  CatalogEntry(type::CatalogType type);
  virtual ~CatalogEntry();

  type::CatalogType getType() const;

  virtual type::Flag* getFlag(type::ColumnType column) = 0;
  virtual type::Integer* getInteger(type::ColumnType column) = 0;
  virtual type::Index* getIndex(type::ColumnType column) = 0;
  virtual type::IntegerRange* getIntegerRange(type::ColumnType column) = 0;
  virtual type::IndexList* getIndexList(type::ColumnType column) = 0;
  virtual type::Float* getFloat(type::ColumnType column) = 0;
  virtual type::TimePoint* getTimePoint(type::ColumnType column) = 0;
  virtual type::String* getString(type::ColumnType column) = 0;
  virtual type::StringList* getStringList(type::ColumnType column) = 0;

  virtual NameMapper* getMapper(type::ColumnType column) = 0;

private:
  type::CatalogType _type;
};

}
