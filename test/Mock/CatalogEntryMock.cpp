#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/NameMapperMock.h"

namespace grb
{
namespace test
{

CatalogEntryMock::CatalogEntryMock()
  : CatalogEntry(type::TEST_CATALOG_ENTRY),
    _flag(false), _integer(0), _index(-1), _float(0.0),
    _integerUnitType(type::UNDEFINED_UNIT), _floatUnitType(type::UNDEFINED_UNIT)
{
  _mapper = new NameMapperMock;
}

CatalogEntryMock::~CatalogEntryMock()
{
  delete _mapper;
}

type::Flag&
CatalogEntryMock::getFlag()
{
  return _flag;
}

type::Integer&
CatalogEntryMock::getInteger()
{
  return _integer;
}

type::Index&
CatalogEntryMock::getIndex()
{
  return _index;
}

type::IntegerRange&
CatalogEntryMock::getIntegerRange()
{
  return _integerRange;
}

type::IndexList&
CatalogEntryMock::getIndexList()
{
  return _indexList;
}

type::Float&
CatalogEntryMock::getFloat()
{
  return _float;
}

type::String&
CatalogEntryMock::getString()
{
  return _string;
}

type::StringList&
CatalogEntryMock::getStringList()
{
  return _stringList;
}

type::Flag*
CatalogEntryMock::getFlag(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_FLAG)
  {
    return &_flag;
  }
  return nullptr;
}

type::Integer*
CatalogEntryMock::getInteger(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_INTEGER)
    return &_integer;
  return nullptr;
}

type::Index*
CatalogEntryMock::getIndex(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_INDEX)
    return &_index;
  return nullptr;
}

type::IntegerRange*
CatalogEntryMock::getIntegerRange(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_INTEGER_RANGE)
    return &_integerRange;
  return nullptr;
}

type::IndexList*
CatalogEntryMock::getIndexList(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_INDEX_LIST)
    return &_indexList;
  return nullptr;
}

type::Float*
CatalogEntryMock::getFloat(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_FLOAT)
    return &_float;
  return nullptr;
}

type::String*
CatalogEntryMock::getString(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_STRING)
    return &_string;
  return nullptr;
}

type::StringList*
CatalogEntryMock::getStringList(type::ColumnType column)
{
  if (column == type::TEST_COLUMN_STRING_LIST)
    return &_stringList;
  return nullptr;
}

NameMapper*
CatalogEntryMock::getMapper(type::ColumnType column)
{
  switch (column)
  {
    case type::TEST_COLUMN_INDEX:
      return _mapper;
    case type::TEST_COLUMN_INDEX_LIST:
      return _mapper;
    default:
      break;
  }
  return nullptr;
}

void
CatalogEntryMock::setUnitType(type::ColumnType column, type::UnitType unitType)
{
  if (column == type::TEST_COLUMN_INTEGER)
    _integerUnitType = unitType;
  else if (column == type::TEST_COLUMN_FLOAT)
    _floatUnitType = unitType;
}

bool
CatalogEntryMock::isValid()
{
  return true;
}

}
}
