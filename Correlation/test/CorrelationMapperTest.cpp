#include "Correlation/CorrelationMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class CorrelationMapperTest
    : public MapperTestFixturesBase<grb::type::CorrelationType, grb::mapper::CorrelationMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_CORRELATION;
    _invalidType = (grb::type::CorrelationType) -1;

    _validName = "undefined-correlation";
    _invalidName = "correlation-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(CorrelationMapperTest)
