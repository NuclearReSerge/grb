#include "test/Mock/NameMapperCommon.h"
#include "test/Mock/NameMapperMock.h"


namespace grb
{
namespace test
{

class NameMapperDummyTest : public NameMapperCommon
{
  void SetUp()
  {
    _mapper = new NameMapperMock;
    _columnType = type::COLUMN_TEST_INDEX;
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

NAME_MAPPER_TESTS(NameMapperDummyTest)

}
}
