#include "Data/ReferenceMapper.h"

#include "test/Mock/NameMapperTestFixtures.h"

namespace testing
{

class ReferenceMapperTest : public NameMapperTestFixturesBase<grb::mapper::ReferenceMapper>
{
protected:
  void SetUp()
  {
    _columnType = grb::type::REFERENCE;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-reference";
    _invalidKey = "invalid-reference";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(ReferenceMapperTest)
