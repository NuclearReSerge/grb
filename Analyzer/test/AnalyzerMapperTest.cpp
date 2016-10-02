#include "Analyzer/AnalyzerMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class AnalyzerMapperTest
    : public MapperTestFixturesBase<grb::type::AnalyzerType, grb::mapper::AnalyzerMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_ANALYZER;
    _invalidType = (grb::type::AnalyzerType) -1;

    _validName = "undefined-analyzer";
    _invalidName = "analyzer-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(AnalyzerMapperTest)
