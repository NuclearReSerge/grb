#include "Model/ModelMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class ModelMapperTest
    : public MapperTestFixturesBase<grb::type::ModelType, grb::mapper::ModelMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_MODEL;
    _invalidType = (grb::type::ModelType) -1;

    _validName = "undefined-model";
    _invalidName = "model-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(ModelMapperTest)
