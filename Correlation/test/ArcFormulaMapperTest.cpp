#include "Correlation/ArcFormulaMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class ArcFormulaMapperTest
    : public MapperTestFixturesBase<grb::type::ArcFormulaType, grb::mapper::ArcFormulaMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_ARC_FORMULA;
    _invalidType = (grb::type::ArcFormulaType) -1;

    _validName = "undefined-arc-formula";
    _invalidName = "arc-formula-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(ArcFormulaMapperTest)
