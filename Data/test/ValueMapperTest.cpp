#include "Data/ValueMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class ValueMapperTest
    : public MapperTestFixturesBase<grb::type::ValueType, grb::mapper::ValueMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_VALUE;
    _invalidType = (grb::type::ValueType) -1;

    _validName = "undefined-value";
    _invalidName = "value-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(ValueMapperTest)
