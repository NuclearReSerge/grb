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
  UNKNOWN_MODEL_TYPE
};

}

class Catalog;

class ModelBase
{
public:
  ModelBase(type::ModelType type = type::UNKNOWN_MODEL_TYPE)
    : _type(type)
  { }

  virtual ~ModelBase()
  { }

  type::ModelType getType() const
  {
    return _type;
  }

  virtual std::size_t generate(Catalog& catalog) = 0;

private:
  type::ModelType _type;
};

}
