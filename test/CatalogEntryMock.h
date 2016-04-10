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

  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);

  NameMapper* getMapper(type::ColumnType column);

protected:
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
