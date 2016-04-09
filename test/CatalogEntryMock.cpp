#include "test/CatalogEntryMock.h"
#include "test/NameMapperMock.h"

namespace grb
{
namespace test
{

CatalogEntryMock::CatalogEntryMock()
  : CatalogEntry(type::CATALOG_TEST)
{
  _mapper = new NameMapperMock;
}

CatalogEntryMock::~CatalogEntryMock()
{
  delete _mapper;
}

type::Flag*
CatalogEntryMock::getFlag(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_FLAG:
      return &_flag;
    default:
      break;
  }
  return nullptr;
}

type::Integer*
CatalogEntryMock::getInteger(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_INTEGER:
      return &_integer;
    default:
      break;
  }
  return nullptr;
}

type::Index*
CatalogEntryMock::getIndex(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_INDEX:
      return &_index;
    default:
      break;
  }
  return nullptr;
}

type::IntegerRange*
CatalogEntryMock::getIntegerRange(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_INTEGER_RANGE:
      return &_integerRange;
    default:
      break;
  }
  return nullptr;
}

type::IndexList*
CatalogEntryMock::getIndexList(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_INDEX_LIST:
      return &_indexList;
    default:
      break;
  }
  return nullptr;
}

type::Float*
CatalogEntryMock::getFloat(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_FLOAT:
      return &_float;
    case type::COLUMN_TEST_COORDINATE:
      return &_coordinate;
    default:
      break;
  }
  return nullptr;
}

type::TimePoint*
CatalogEntryMock::getTimePoint(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_TIMEPOINT:
      return &_timepoint;
    default:
      break;
  }
  return nullptr;
}

type::String*
CatalogEntryMock::getString(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_STRING:
      return &_string;
    default:
      break;
  }
  return nullptr;
}

type::StringList*
CatalogEntryMock::getStringList(type::ColumnType column)
{
  switch (column)
  {
    case type::COLUMN_TEST_STRING_LIST:
      return &_stringList;
    default:
      break;
  }
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

}
}
