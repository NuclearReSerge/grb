#pragma once

namespace grb
{
namespace type
{

enum ModelType
{
  // ISOTROPIC MODELS
  ISOTROPIC_SPHERE,
  ISOTROPIC_BALL,
  ISOTROPIC_JUMPER_CONST_DISTANCE,
  ISOTROPIC_JUMPER_GAUSSIAN_DISTANCE,

  // ANISOTROPIC MODELS
  MILKYWAY_JUMPER,
  MILKYWAY_JUMPER_WITH_CLUSTERS,
  MILKYWAY_JUMPER_EXPLORER,

  // LAST
  UNDEFINED_MODEL
};

}
}
