#include "Filter/FilterFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class FilterFactoryTest :
    public FactoryTestFixturesBase<grb::type::FilterType, grb::Filter, grb::factory::FilterFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_FILTER;
    _invalidName = "undefined-filter";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(FilterFactoryTest)

namespace testing
{

TEST_F(FilterFactoryTest, createName_None)
{
  _validType = grb::type::FILTER_NONE;
  _validName = "none";
  callCreateName();
}

} // namespace testing
