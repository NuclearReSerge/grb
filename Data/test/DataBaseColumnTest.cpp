#include "Data/DataBaseColumn.h"

#include <gmock/gmock.h>

namespace testing
{

class DataBaseColumnTest : public Test
{
protected:
  grb::DataBaseColumn* _dbColumn;

};

TEST_F(DataBaseColumnTest, init_Default)
{
  _dbColumn = new grb::DataBaseColumn;

  ASSERT_EQ(grb::type::UNDEFINED_COLUMN,_dbColumn->getColumnType());
  ASSERT_EQ(grb::type::UNDEFINED_VALUE,_dbColumn->getValueType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT,_dbColumn->getUnitType());
  ASSERT_FALSE(_dbColumn->isColumnRequired());

  delete _dbColumn;
}

TEST_F(DataBaseColumnTest, init_Custom)
{
  const grb::type::ColumnType columnType = grb::type::RECORD_NUMBER;
  const grb::type::ValueType valueType = grb::type::FLAG;
  const grb::type::UnitType unitType = grb::type::NO_UNIT;

  _dbColumn = new grb::DataBaseColumn(columnType, true, unitType, valueType);

  ASSERT_EQ(columnType,_dbColumn->getColumnType());
  ASSERT_EQ(valueType,_dbColumn->getValueType());
  ASSERT_EQ(unitType,_dbColumn->getUnitType());
  ASSERT_TRUE(_dbColumn->isColumnRequired());

  delete _dbColumn;
}


} // namespace testing
