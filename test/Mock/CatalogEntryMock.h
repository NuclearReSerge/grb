#include "Data/CatalogEntry.h"

#pragma once

namespace grb
{

namespace test
{

class CatalogEntryMock : public CatalogEntry
{
public:
  CatalogEntryMock();
  ~CatalogEntryMock();

  type::Flag& getFlag();
  type::Integer& getInteger();
  type::Index& getIndex();
  type::IntegerRange& getIntegerRange();
  type::IndexList& getIndexList();
  type::Float& getFloat();
  type::String& getString();
  type::StringList& getStringList();

protected:
  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);

  NameMapper* getMapper(type::ColumnType column);

  void setUnitType(type::ColumnType column, type::UnitType unitType);

  bool isValid();

private:
  type::Flag _flag;
  type::Integer _integer;
  type::Index _index;
  type::IntegerRange _integerRange;
  type::IndexList _indexList;
  type::Float _float;
  type::String _string;
  type::StringList _stringList;
  type::UnitType _integerUnitType;
  type::UnitType _floatUnitType;
  NameMapper* _mapper;
};

}
}
