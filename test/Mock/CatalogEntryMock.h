#pragma once

#include "Catalog/CatalogEntry.h"

#include <gmock/gmock.h>

namespace grb
{

class CatalogEntryMock : public CatalogEntry
{
public:
  CatalogEntryMock(const type::CatalogType type)
    : CatalogEntry(type)
  {
  }

  MOCK_METHOD1(getFlag, type::Flag*(type::ColumnType column));
  MOCK_METHOD1(getInteger, type::Integer*(type::ColumnType column));
  MOCK_METHOD1(getIndex, type::Index*(type::ColumnType column));
  MOCK_METHOD1(getIntegerRange, type::IntegerRange*(type::ColumnType column));
  MOCK_METHOD1(getIndexList, type::IndexList*(type::ColumnType column));
  MOCK_METHOD1(getFloat, type::Float*(type::ColumnType column));
  MOCK_METHOD1(getString, type::String*(type::ColumnType column));
  MOCK_METHOD1(getStringList, type::StringList*(type::ColumnType column));

  MOCK_METHOD1(getMapper, mapper::NameMapper*(type::ColumnType column));

  MOCK_METHOD2(setUnitType, void(type::ColumnType column, type::UnitType unitType));

  MOCK_METHOD0(isValid, bool());
};

} // namespace grb
