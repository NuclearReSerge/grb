#include "test/Mock/DataBaseFormatMock.h"

#include "Data/DataBaseFormatMapper.h"
//#include "Data/DataType.h"

namespace grb
{
namespace test
{

DataBaseFormatMock::DataBaseFormatMock()
  : DataBaseFormat(type::TEST_DATABASE_TABLE)
{
}

void
DataBaseFormatMock::initialize()
{
  addDataType(new DataType(type::TEST_COLUMN_FLAG,          false, type::NO_UNIT, type::FLAG));
  addDataType(new DataType(type::TEST_COLUMN_INTEGER,       false, type::NO_UNIT, type::INTEGER));
  addDataType(new DataType(type::TEST_COLUMN_INDEX,         false, type::NO_UNIT, type::INDEX));
  addDataType(new DataType(type::TEST_COLUMN_INTEGER_RANGE, false, type::NO_UNIT, type::INTEGER_RANGE));
  addDataType(new DataType(type::TEST_COLUMN_INDEX_LIST,    false, type::NO_UNIT, type::INDEX_LIST));
  addDataType(new DataType(type::TEST_COLUMN_FLOAT,         false, type::NO_UNIT, type::FLOAT));
  addDataType(new DataType(type::TEST_COLUMN_STRING,        false, type::NO_UNIT, type::STRING));
  addDataType(new DataType(type::TEST_COLUMN_STRING_LIST,   false, type::NO_UNIT, type::STRING_LIST));

  setColumnFlags();
}

void
DataBaseFormatMock::setColumnFlag(std::size_t column, bool required)
{
  DataBaseFormat::setColumnFlag(column, required);
}

}
}
