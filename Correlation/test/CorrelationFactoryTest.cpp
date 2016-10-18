#include "Correlation/CorrelationFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class CorrelationFactoryTest :
    public FactoryTestFixturesBase<grb::type::CorrelationType, grb::Correlation, grb::factory::CorrelationFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_CORRELATION;
    _invalidName = "undefined-correlation";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(CorrelationFactoryTest)

namespace testing
{

TEST_F(CorrelationFactoryTest, createName_CorrelationTimeArcGrbcat)
{
  _validType = grb::type::CORRELATION_GRBCAT_DTDARC;
  _validName = "dtdarc";
  callCreateName();
}

} // namespace testing
