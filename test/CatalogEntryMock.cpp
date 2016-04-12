#include "test/CatalogEntryMock.h"

#include "test/NameMapperMock.h"

namespace grb
{
namespace test
{

CatalogEntryMock::CatalogEntryMock()
  : CatalogEntry(type::CATALOG_TEST),
    _flag(false), _integer(0), _index(-1), _float(0.0)
{
  _mapper = new NameMapperMock;
}

CatalogEntryMock::~CatalogEntryMock()
{
  delete _mapper;
}

const type::Flag&
CatalogEntryMock::getFlag() const
{ return _flag; }

const type::Integer&
CatalogEntryMock::getInteger() const
{ return _integer; }

const type::Index&
CatalogEntryMock::getIndex() const
{ return _index; }

const type::IntegerRange&
CatalogEntryMock::getIntegerRange() const
{ return _integerRange; }

const type::IndexList&
CatalogEntryMock::getIndexList() const
{ return _indexList; }

const type::Float&
CatalogEntryMock::getFloat() const
{ return _float; }

const type::String&
CatalogEntryMock::getString() const
{ return _string; }

const type::StringList&
CatalogEntryMock::getStringList() const
{ return _stringList; }

type::Flag*
CatalogEntryMock::getFlag(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_FLAG)
    return &_flag;
  return nullptr;
}

type::Integer*
CatalogEntryMock::getInteger(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_INTEGER)
      return &_integer;
  return nullptr;
}

type::Index*
CatalogEntryMock::getIndex(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_INDEX)
      return &_index;
  return nullptr;
}

type::IntegerRange*
CatalogEntryMock::getIntegerRange(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_INTEGER_RANGE)
      return &_integerRange;
  return nullptr;
}

type::IndexList*
CatalogEntryMock::getIndexList(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_INDEX_LIST)
      return &_indexList;
  return nullptr;
}

type::Float*
CatalogEntryMock::getFloat(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_FLOAT)
      return &_float;
  return nullptr;
}

type::String*
CatalogEntryMock::getString(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_STRING)
      return &_string;
  return nullptr;
}

type::StringList*
CatalogEntryMock::getStringList(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_STRING_LIST)
      return &_stringList;
  return nullptr;
}

NameMapper*
CatalogEntryMock::getMapper(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_INDEX:
      return _mapper;
    case type::COLUMN_TEST_INDEX_LIST:
      return _mapper;
    default:
      break;
  }
  return nullptr;
}

bool
CatalogEntryMock::isValid()
{
  return true;
}


}
}
