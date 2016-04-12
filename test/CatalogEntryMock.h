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

  const type::Flag& getFlag() const { return _flag; }
  const type::Integer& getInteger() const { return _integer; }
  const type::Index& getIndex() const { return _index; }
  const type::IntegerRange& getIntegerRange() const { return _integerRange; }
  const type::IndexList& getIndexList() const { return _indexList; }
  const type::Float& getFloat() const { return _float; }
  const type::String& getString() const { return _string; }
  const type::StringList& getStringList() const { return _stringList; }

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
  NameMapper* _mapper;
};

}
}
