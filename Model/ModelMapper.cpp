#include "Model/ModelMapper.h"

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

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& ModelMapper::getList() const
{
  return MODEL_NAMES;
}

} // namespace mapper
} // namespace grb
