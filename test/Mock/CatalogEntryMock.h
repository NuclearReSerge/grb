#include "Data/CatalogEntry.h"

#pragma once

namespace grb
{

class CatalogEntryMock : public CatalogEntry
{
public:
  CatalogEntryMock();
  ~CatalogEntryMock();

  type::Flag& getFlag()
  {
    return _flag;
  }

  type::Integer& getInteger()
  {
    return _integer;
  }

  type::Index& getIndex()
  {
    return _index;
  }

  type::IntegerRange& getIntegerRange()
  {
    return _integerRange;
  }

  type::IndexList& getIndexList()
  {
    return _indexList;
  }

  type::Float& getFloat()
  {
    return _float;
  }

  type::String& getString()
  {
    return _string;
  }

  type::StringList& getStringList()
  {
    return _stringList;
  }

protected:
  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);

  mapper::NameMapper* getMapper(type::ColumnType column);

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
  mapper::NameMapper* _mapper;
};

} // namespace grb
