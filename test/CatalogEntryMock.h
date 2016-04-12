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

  const type::Flag& getFlag() const;
  const type::Integer& getInteger() const;
  const type::Index& getIndex() const;
  const type::IntegerRange& getIntegerRange() const;
  const type::IndexList& getIndexList() const;
  const type::Float& getFloat() const;
  const type::String& getString() const;
  const type::StringList& getStringList() const;

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
