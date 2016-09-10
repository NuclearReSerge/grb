#include "Data/TimeDefMapper.h"

#include "test/Mock/NameMapperTestBase.h"

#include <gtest/gtest.h>

namespace testing
{

class TimeDefMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::TimeDefMapper::instance();
    _columnType = grb::type::TIME_DEF;
    _first = "BAT trigger";
    _last = "Trigger Time";
    _firstIdx = 0;
    _lastIdx = 6;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(TimeDefMapperTest)
