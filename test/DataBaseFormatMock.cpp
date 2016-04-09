#include "test/DataBaseFormatMock.h"

namespace grb
{
namespace test
{

DataBaseFormatMock::DataBaseFormatMock()
  : DataBaseFormat(type::DATABASE_TABLE_TEST)
{
}

void
DataBaseFormatMock::initialize() throw(Exception)
{
  _format.push_back(new DataType(type::COLUMN_TEST_FLAG,          false, type::NO_UNIT, type::FLAG));
  _format.push_back(new DataType(type::COLUMN_TEST_INTEGER,       false, type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::COLUMN_TEST_INDEX,         false, type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::COLUMN_TEST_INTEGER_RANGE, false, type::NO_UNIT, type::INTEGER_RANGE));
  _format.push_back(new DataType(type::COLUMN_TEST_INDEX_LIST,    false, type::NO_UNIT, type::INDEX_LIST));
  _format.push_back(new DataType(type::COLUMN_TEST_FLOAT,         false, type::NO_UNIT, type::FLOAT));
  _format.push_back(new DataType(type::COLUMN_TEST_TIMEPOINT,     false, type::NO_UNIT, type::TIMEPOINT));
  _format.push_back(new DataType(type::COLUMN_TEST_COORDINATE,    false, type::NO_UNIT, type::COORDINATE));
  _format.push_back(new DataType(type::COLUMN_TEST_STRING,        false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::COLUMN_TEST_STRING_LIST,   false, type::NO_UNIT, type::STRING_LIST));

  setupRequiredColumns();
}

std::vector<DataType*>&
DataBaseFormatMock::getFormatVector()
{
  return _format;
}

void
DataBaseFormatMock::setCoordinateSystem(type::CoordinateSystemType coordSys)
{
  _coordSys = coordSys;
}

void
DataBaseFormatMock::setColumnRequired(std::size_t pos, bool val)
{
  _requiredFlags.set(pos, val);
}

}
}
