#include "Data/TimeDef.h"

#include "Tools/test/NameMapperTest.h"
#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class TimeDefTest : public NameMapperTest
{
  void SetUp()
  {
    _mapper = TimeDef::instance();
    _columnType = type::TIME_DEF;
    _first = "BAT trigger";
    _last = "Trigger time";
    _firstIdx = 0;
    _lastIdx = 6;
  }
};

NAME_MAPPER_TESTS(TimeDefTest)

}
}
