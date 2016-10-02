#include "Data/TimeDefMapper.h"

#include "test/Mock/NameMapperTestFixtures.h"

namespace testing
{

class TimeDefMapperTest : public NameMapperTestFixturesBase<grb::mapper::TimeDefMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::TIME_DEF;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-time-def";
    _invalidKey = "invalid-time-def";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(TimeDefMapperTest)
