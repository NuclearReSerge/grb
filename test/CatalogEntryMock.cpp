#include "test/CatalogEntryMock.h"

#include "Data/Catalog.h"
#include "test/NameMapperMock.h"

#include "Common/trace.h"

namespace grb
{
namespace test
{

CatalogEntryMock::CatalogEntryMock(const Catalog& catalog)
  : CatalogEntry(catalog),
    _flag(false), _integer(0), _index(-1), _float(0.0),
    _integerUnitType(type::UNIT_TYPE_UNDEFINED), _floatUnitType(type::UNIT_TYPE_UNDEFINED)
{
  _mapper = new NameMapperMock;
}

CatalogEntryMock::~CatalogEntryMock()
{
  delete _mapper;
}

const type::Flag&
CatalogEntryMock::getFlag() const
{
  return _flag;
}

const type::Integer&
CatalogEntryMock::getInteger() const
{
  return _integer;
}

const type::Index&
CatalogEntryMock::getIndex() const
{
  return _index;
}

const type::IntegerRange&
CatalogEntryMock::getIntegerRange() const
{
  return _integerRange;
}

const type::IndexList&
CatalogEntryMock::getIndexList() const
{
  return _indexList;
}

const type::Float&
CatalogEntryMock::getFloat() const
{
  return _float;
}

const type::String&
CatalogEntryMock::getString() const
{
  return _string;
}

const type::StringList&
CatalogEntryMock::getStringList() const
{
  return _stringList;
}

type::Flag*
CatalogEntryMock::getFlag(type::ColumnType column)
{
  if (column == type::COLUMN_TEST_FLAG)
  {
    return &_flag;
  }
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

void
CatalogEntryMock::setUnitType(type::ColumnType column, type::UnitType unitType)
{
  if (column == type::COLUMN_TEST_INTEGER)
    _integerUnitType = unitType;
  else if (column == type::COLUMN_TEST_FLOAT)
    _floatUnitType = unitType;
}

bool
CatalogEntryMock::isValid()
{
  return true;
}

}
}
