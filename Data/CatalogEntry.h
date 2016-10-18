#include "Common/Global.h"
#include "Data/CatalogType.h"
#include "Data/ColumnType.h"
#include "Data/UnitType.h"

#pragma once

namespace grb
{
namespace mapper
{

class NameMapper;

} // namespace mapper

class CatalogEntry
{
public:
  CatalogEntry(type::CatalogType type = type::UNDEFINED_CATALOG)
    : _type(type)
  {
  }

  virtual ~CatalogEntry() = default;

  type::CatalogType getType() const
  {
    return _type;
  }

  virtual bool isValid() = 0;

protected:
  friend class ParserDatabase;

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

private:
  type::CatalogType _type;
};

} // namespace grb
