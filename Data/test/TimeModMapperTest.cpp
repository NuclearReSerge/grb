#include "Data/TimeModMapper.h"

#include "test/Mock/NameMapperTestFixtures.h"

namespace testing
{

class Time50ModMapperTest : public NameMapperTestFixturesBase<grb::mapper::Time50ModMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::T50_MOD;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-time-mod";
    _invalidKey = "invalid-time-mod";
  }
};

class Time90ModMapperTest : public NameMapperTestFixturesBase<grb::mapper::Time90ModMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::T90_MOD;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-time-mod";
    _invalidKey = "invalid-time-mod";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(Time50ModMapperTest)
NAME_MAPPER_TEST_FIXTURES(Time90ModMapperTest)

