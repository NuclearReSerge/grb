#include "Data/RegionMapper.h"

#include "test/Mock/NameMapperTestFixtures.h"

namespace testing
{

class RegionMapperTest : public NameMapperTestFixturesBase<grb::mapper::RegionMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::REGION;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-region";
    _invalidKey = "invalid-region";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(RegionMapperTest)
