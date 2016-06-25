#include "Model/ModelFactory.h"
#include "Model/ModelBase.h"

#include "Model/IsotropicSphereModel.h"
#include "Model/IsotropicBallModel.h"


namespace grb
{

ModelFactoryType::ModelFactoryType()
{
}

ModelBase*
ModelFactoryType::create(type::ModelType modelType)
{
  switch (modelType)
  {
    // ISOTROPIC MODELS
    case type::ISOTROPIC_SPHERE:
      return new IsotropicSphereModel;
    case type::ISOTROPIC_BALL:
      return new IsotropicBallModel;
    case type::ISOTROPIC_JUMPER_CONST_DISTANCE:
      break;
    case type::ISOTROPIC_JUMPER_GAUSSIAN_DISTANCE:
      break;
    // ANISOTROPIC MODELS
    case type::MILKYWAY_JUMPER:
      break;
    case type::MILKYWAY_JUMPER_WITH_CLUSTERS:
      break;
    case type::MILKYWAY_JUMPER_EXPLORER:
      break;
    default:
      break;
  }
  return nullptr;
}

}
