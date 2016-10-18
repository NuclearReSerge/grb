#include "Model/ModelCmdMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class ModelCmdMapperTest
    : public MapperTestFixturesBase<grb::type::ModelCmdType, grb::mapper::ModelCmdMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_MODEL_CMD;
    _invalidType = (grb::type::ModelCmdType) -1;

    _validName = "undefined-model-command";
    _invalidName = "model-command-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(ModelCmdMapperTest)
