#include "Data/CoordinateSystemMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class CoordinateSystemMapperTest
    : public MapperTestFixturesBase<grb::type::CoordinateSystemType, grb::mapper::CoordinateSystemMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_COORDINATE_SYSTEM;
    _invalidType = (grb::type::CoordinateSystemType) -1;

    _validName = "undefined-coordinate-system";
    _invalidName = "coordinate-system-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(CoordinateSystemMapperTest)
