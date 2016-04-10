#include "Common/Global.h"

#pragma once

namespace grb
{

class NameMapper;

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
  virtual type::String* getString(type::ColumnType column) = 0;
  virtual type::StringList* getStringList(type::ColumnType column) = 0;

  virtual NameMapper* getMapper(type::ColumnType column) = 0;

  virtual bool isValid() = 0;

private:
  type::CatalogType _type;
};

}
