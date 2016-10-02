#include "Data/UnitMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class UnitMapperTest
    : public MapperTestFixturesBase<grb::type::UnitType, grb::mapper::UnitMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_UNIT;
    _invalidType = (grb::type::UnitType) -1;

    _validName = "undefined-unit";
    _invalidName = "unit-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(UnitMapperTest)
