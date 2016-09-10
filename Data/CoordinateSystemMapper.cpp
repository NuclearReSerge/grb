#include "Data/CoordinateSystemMapper.h"

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

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>&
CoordinateSystemMapper::getList() const
{
  return COORDINATE_SYSTEM_NAMES;
}

} // namespace mapper
} // namespace grb
