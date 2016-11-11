#include "Database/DatabaseColumn.h"

#include <gmock/gmock.h>

namespace testing
{

class DatabaseColumnTest : public Test
{
protected:
  grb::DatabaseColumn* _dbColumn;

};

TEST_F(DatabaseColumnTest, init_Default)
{
  _dbColumn = new grb::DatabaseColumn;

  ASSERT_EQ(grb::type::UNDEFINED_COLUMN,_dbColumn->getColumnType());
  ASSERT_EQ(grb::type::UNDEFINED_VALUE,_dbColumn->getValueType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT,_dbColumn->getUnitType());
  ASSERT_FALSE(_dbColumn->isColumnRequired());

  delete _dbColumn;
}

TEST_F(DatabaseColumnTest, init_Custom)
{
  const grb::type::ColumnType columnType = grb::type::RECORD_NUMBER;
  const grb::type::ValueType valueType = grb::type::FLAG;
  const grb::type::UnitType unitType = grb::type::NO_UNIT;

  _dbColumn = new grb::DatabaseColumn(columnType, unitType, valueType, true);

  ASSERT_EQ(columnType,_dbColumn->getColumnType());
  ASSERT_EQ(valueType,_dbColumn->getValueType());
  ASSERT_EQ(unitType,_dbColumn->getUnitType());
  ASSERT_TRUE(_dbColumn->isColumnRequired());

  delete _dbColumn;
}


} // namespace testing
