#include "Filter/FilterMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class FilterMapperTest
    : public MapperTestFixturesBase<grb::type::FilterType, grb::mapper::FilterMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_FILTER;
    _invalidType = (grb::type::FilterType) -1;

    _validName = "undefined-filter";
    _invalidName = "filter-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(FilterMapperTest)
