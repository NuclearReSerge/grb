#pragma once

namespace grb
{
namespace type
{

enum CoordinateSystemType
{
  // math
  CARTESIAN,
  CYLINDRICAL,
  SPHERICAL,
  // astronomy
  EQUATORIAL_B1950,
  EQUATORIAL_J2000,
  ECLIPTIC,
  GALACTIC,

  // LAST
  UNDEFINED_COORDINATE_SYSTEM
};

} // namespace type
} // namespace grb
