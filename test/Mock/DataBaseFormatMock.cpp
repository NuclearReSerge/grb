#include "test/Mock/DataBaseFormatMock.h"

namespace grb
{

void
DataBaseFormatMock::initialize()
{
  addColumn(new DataBaseColumn(type::TEST_COLUMN_FLAG,          false, type::NO_UNIT, type::FLAG));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_INTEGER,       false, type::NO_UNIT, type::INTEGER));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_INDEX,         false, type::NO_UNIT, type::INDEX));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_INTEGER_RANGE, false, type::NO_UNIT, type::INTEGER_RANGE));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_INDEX_LIST,    false, type::NO_UNIT, type::INDEX_LIST));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_FLOAT,         false, type::NO_UNIT, type::FLOAT));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_STRING,        false, type::NO_UNIT, type::STRING));
  addColumn(new DataBaseColumn(type::TEST_COLUMN_STRING_LIST,   false, type::NO_UNIT, type::STRING_LIST));

  setColumnFlags();
}

} // namespace grb
