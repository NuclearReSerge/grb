#include "Model/ModelFactory.h"

#include "Model/IsotropicSphereModel.h"
#include "Model/IsotropicBallModel.h"

namespace grb
{
namespace factory
{

Model*
ModelFactory::createType(const type::ModelType& modelType)
{
  switch (modelType)
  {
    // ISOTROPIC MODELS
    case type::ISOTROPIC_SPHERE:
      return new IsotropicSphereModel;
    case type::ISOTROPIC_BALL:
      return new IsotropicBallModel;
    case type::ISOTROPIC_JUMPER_CONST_DISTANCE:
    case type::ISOTROPIC_JUMPER_GAUSSIAN_DISTANCE:
    // ANISOTROPIC MODELS
    case type::MILKYWAY_JUMPER:
    case type::MILKYWAY_JUMPER_WITH_CLUSTERS:
    case type::MILKYWAY_JUMPER_EXPLORER:
    default:
      break;
  }
  return nullptr;
}

} // namespace factory
} // namespace grb
