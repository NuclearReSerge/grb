#include "Model/ModelMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> MODEL_NAMES
{
  // ISOTROPIC MODELS
  "isotropic-sphere",
  "isotropic-ball",
  "isotropic-jumper-const-distance",
  "isotropic-jumper-gaussian-distance",

  // ANISOTROPIC MODELS
  "milkyway-jumper",
  "milkyway-jumper-with-clusters",
  "milkyway-jumper-explorer",

  // LAST
  "undefined-model"
};

}

namespace mapper
{

ModelMapper::ModelMapper()
{
  initiate();
}

const std::vector<std::string>& ModelMapper::getList() const
{
  return MODEL_NAMES;
}

}

}
