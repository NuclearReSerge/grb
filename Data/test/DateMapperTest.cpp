#include "Data/DateMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class DateMapperTest
    : public MapperTestFixturesBase<grb::type::DateType, grb::mapper::DateMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_DATE;
    _invalidType = (grb::type::DateType) -1;

    _validName = "undefined-date";
    _invalidName = "date-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(DateMapperTest)
