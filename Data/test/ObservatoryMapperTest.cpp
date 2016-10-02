#include "Data/ObservatoryMapper.h"

#include "test/Mock/NameMapperTestFixtures.h"

namespace testing
{

class ObservatoryMapperTest : public NameMapperTestFixturesBase<grb::mapper::ObservatoryMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::OBSERVATORY;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-observatory";
    _invalidKey = "invalid-observatory";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(ObservatoryMapperTest)
