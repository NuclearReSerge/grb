#include "test/Mock/NameMapperTestBase.h"
#include "test/Mock/NameMapperMock.h"


namespace testing
{

class NameMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = new grb::mapper::NameMapperMock;
    _columnType = grb::type::TEST_COLUMN_INDEX;
    _firstIdx = 0;
    _lastIdx = 1;
    _first = "NAME_LIST_FIRST";
    _last = "NAME_LIST_LAST";
  }

  void TearDown()
  {
    delete _mapper;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(NameMapperTest)
