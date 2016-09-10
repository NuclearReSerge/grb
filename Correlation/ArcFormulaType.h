#pragma once

namespace grb
{
namespace type
{

enum ArcFormulaType
{
  SPHERICAL_LAW_OF_COSINES,
  HAVERSINE_FORMULA,
  VINCENTY_FORMULAE,

  // LAST
  UNDEFINED_ARC_FORMULA
};

} // namespace type
} // namespace grb
