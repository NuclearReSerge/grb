#include "test/Mock/DatabaseMock.h"

#include <gtest/gtest.h>

namespace testing
{

class DatabaseTest : public Test
{
protected:
  grb::DatabaseMock _format {grb::type::UNDEFINED_DATABASE};
};

TEST_F(DatabaseTest, init)
{
  ASSERT_EQ(grb::type::UNDEFINED_DATABASE, _format.getType());
  ASSERT_TRUE(_format.getRequiredColumns().none());
  ASSERT_TRUE(_format.getDataTypes().empty());
}

TEST_F(DatabaseTest, addColumn)
{
  grb::DatabaseColumn* column = new grb::DatabaseColumn;
  _format.addColumn(column);
  ASSERT_FALSE(_format.getDataTypes().empty());
}

TEST_F(DatabaseTest, setColumnFlag)
{
  for (size_t i = 0;  i< grb::type::UNDEFINED_COLUMN; ++i)
    _format.setColumnFlag(i);

  ASSERT_TRUE(_format.getRequiredColumns().all());
}


TEST_F(DatabaseTest, setColumnFlags)
{
  grb::DatabaseColumn* column;

  column = new grb::DatabaseColumn(grb::type::RECORD_NUMBER, grb::type::NO_UNIT, grb::type::INTEGER, true);
  _format.addColumn(column);
  column = new grb::DatabaseColumn(grb::type::NAME, grb::type::NO_UNIT, grb::type::STRING, false);
  _format.addColumn(column);
  _format.setColumnFlags();

  ASSERT_TRUE(_format.getRequiredColumns().test(grb::type::RECORD_NUMBER));
  ASSERT_FALSE(_format.getRequiredColumns().test(grb::type::NAME));
}

} // namespace testing
