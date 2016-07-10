#include "Correlation/ArcFormulaMapper.h"

namespace grb
{

namespace
{

static std::vector<std::string> ARC_FORMULA_NAMES
{
  "spherical-law-of-cosines",
  "Haversine-formula",
  "Vincenty-formulae",

  // LAST
  "undefined-arc-formula"
};

}

namespace mapper
{

ArcFormulaMapper::ArcFormulaMapper()
{
  initiate();
}

const std::vector<std::string>& ArcFormulaMapper::getList() const
{
  return ARC_FORMULA_NAMES;
}

}

}
