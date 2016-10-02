#include "Analyzer/AnalyzerCmdMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class AnalyzerCmdMapperTest
    : public MapperTestFixturesBase<grb::type::AnalyzerCmdType, grb::mapper::AnalyzerCmdMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_ANALYZER_CMD;
    _invalidType = (grb::type::AnalyzerCmdType) -1;

    _validName = "undefined-analyzer-cmd";
    _invalidName = "analyzer-cmd-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(AnalyzerCmdMapperTest)
