#include "Correlation/ArcFormulaMapper.h"

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

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>&
ArcFormulaMapper::getList() const
{
  return ARC_FORMULA_NAMES;
}

} // namespace mapper
} // namespace grb
