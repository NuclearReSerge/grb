#include "test/DataBaseFormatMock.h"

#include "Data/DataType.h"

namespace grb
{
namespace test
{

DataBaseFormatMock::DataBaseFormatMock()
  : DataBaseFormat(type::DATABASE_TABLE_TEST)
{
}

void
DataBaseFormatMock::initialize()
{
  addDataType(new DataType(type::COLUMN_TEST_FLAG,          false, type::NO_UNIT, type::FLAG));
  addDataType(new DataType(type::COLUMN_TEST_INTEGER,       false, type::NO_UNIT, type::INTEGER));
  addDataType(new DataType(type::COLUMN_TEST_INDEX,         false, type::NO_UNIT, type::INDEX));
  addDataType(new DataType(type::COLUMN_TEST_INTEGER_RANGE, false, type::NO_UNIT, type::INTEGER_RANGE));
  addDataType(new DataType(type::COLUMN_TEST_INDEX_LIST,    false, type::NO_UNIT, type::INDEX_LIST));
  addDataType(new DataType(type::COLUMN_TEST_FLOAT,         false, type::NO_UNIT, type::FLOAT));
  addDataType(new DataType(type::COLUMN_TEST_STRING,        false, type::NO_UNIT, type::STRING));
  addDataType(new DataType(type::COLUMN_TEST_STRING_LIST,   false, type::NO_UNIT, type::STRING_LIST));

  setColumnFlags();
}

void
DataBaseFormatMock::setColumnFlag(std::size_t column, bool required)
{
  DataBaseFormat::setColumnFlag(column, required);
}

}
}
