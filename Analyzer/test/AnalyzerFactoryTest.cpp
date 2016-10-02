#include "Analyzer/AnalyzerFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class AnalyzerFactoryTest :
    public FactoryTestFixturesBase<grb::type::AnalyzerType, grb::Analyzer, grb::factory::AnalyzerFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_ANALYZER;
    _invalidName = "undefined-analyzer";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(AnalyzerFactoryTest)


namespace testing
{

TEST_F(AnalyzerFactoryTest, createName_AnalyzerGrbcat)
{
  _validType = grb::type::GRBCAT_ANALYZER;
  _validName = "grbcat-analyzer";
  callCreateName();
}

TEST_F(AnalyzerFactoryTest, createType_AnalyzerGrbcat)
{
  _validType = grb::type::GRBCAT_ANALYZER;
  callCreateType();
}

} // namespace testing

