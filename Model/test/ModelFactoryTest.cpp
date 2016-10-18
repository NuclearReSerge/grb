#include "Model/ModelFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class ModelFactoryTest :
    public FactoryTestFixturesBase<grb::type::ModelType, grb::Model, grb::factory::ModelFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_MODEL;
    _invalidName = "undefined-model";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(ModelFactoryTest)

namespace testing
{

TEST_F(ModelFactoryTest, createName_IsotropicSphere)
{
  _validType = grb::type::ISOTROPIC_SPHERE;
  _validName = "isotropic-sphere";
  callCreateName();
}

TEST_F(ModelFactoryTest, createName_IsotropicBall)
{
  _validType = grb::type::ISOTROPIC_BALL;
  _validName = "isotropic-ball";
  callCreateName();
}
/*
TEST_F(ModelFactoryTest, createName_IsotropicJumperConstDistance)
{
  _validType = grb::type::ISOTROPIC_JUMPER_CONST_DISTANCE;
  _validName = "isotropic-jumper-const-distance";
  callCreateName();
}

TEST_F(ModelFactoryTest, createName_IsotropicJumperGaussianDistance)
{
  _validType = grb::type::ISOTROPIC_JUMPER_GAUSSIAN_DISTANCE;
  _validName = "isotropic-jumper-gaussian-distance";
  callCreateName();
}

TEST_F(ModelFactoryTest, createName_MilkywayJumper)
{
  _validType = grb::type::MILKYWAY_JUMPER;
  _validName = "milkyway-jumper";
  callCreateName();
}

TEST_F(ModelFactoryTest, createName_MilkywayJumperWithClusters)
{
  _validType = grb::type::MILKYWAY_JUMPER_WITH_CLUSTERS;
  _validName = "milkyway-jumper-with-clusters";
  callCreateName();
}

TEST_F(ModelFactoryTest, createName_MilkywayJumperExplorer)
{
  _validType = grb::type::MILKYWAY_JUMPER_EXPLORER;
  _validName = "milkyway-jumper-explorer";
  callCreateName();
}
*/
} // namespace testing
