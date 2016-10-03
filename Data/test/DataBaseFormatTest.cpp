#include "test/Mock/DataBaseFormatMock.h"

#include <gtest/gtest.h>

namespace testing
{

class DataBaseFormatTest : public Test
{
protected:
  grb::DataBaseFormatMock _format {grb::type::UNDEFINED_DATABASE_FORMAT};
};

TEST_F(DataBaseFormatTest, init)
{
  ASSERT_EQ(grb::type::UNDEFINED_DATABASE_FORMAT, _format.getType());
  ASSERT_TRUE(_format.getRequiredColumns().none());
  ASSERT_TRUE(_format.getDataTypes().empty());
}

TEST_F(DataBaseFormatTest, addColumn)
{
  grb::DataBaseColumn* column = new grb::DataBaseColumn;
  _format.addColumn(column);
  ASSERT_FALSE(_format.getDataTypes().empty());
}

TEST_F(DataBaseFormatTest, setColumnFlag)
{
  for (size_t i = 0;  i< grb::type::UNDEFINED_COLUMN; ++i)
    _format.setColumnFlag(i);

  ASSERT_TRUE(_format.getRequiredColumns().all());
}


TEST_F(DataBaseFormatTest, setColumnFlags)
{
  grb::DataBaseColumn* column;

  column = new grb::DataBaseColumn(grb::type::RECORD_NUMBER, true, grb::type::NO_UNIT, grb::type::INTEGER);
  _format.addColumn(column);
  column = new grb::DataBaseColumn(grb::type::NAME, false, grb::type::NO_UNIT, grb::type::STRING);
  _format.addColumn(column);
  _format.setColumnFlags();

  ASSERT_TRUE(_format.getRequiredColumns().test(grb::type::RECORD_NUMBER));
  ASSERT_FALSE(_format.getRequiredColumns().test(grb::type::NAME));
}

} // namespace testing
