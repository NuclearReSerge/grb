#include "Data/CoordinateSystemMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> COORDINATE_SYSTEM_NAMES
{
  // math
  "cartesian",
  "cylindrical",
  "spherical",
  // astronomy
  "B1950",
  "J2000",
  "ecliptic",
  "galactic",

  // LAST
  "undefined-coordinate-system"
};

}

namespace mapper
{

CoordinateSystemMapper::CoordinateSystemMapper()
{
  initiate();
}

const std::vector<std::string>& CoordinateSystemMapper::getList() const
{
  return COORDINATE_SYSTEM_NAMES;
}

}

}
