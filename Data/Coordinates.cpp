#include "Data/Coordinates.h"

#include <cmath>

//typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
/*
JD(0) = -4713-01-01 12:00:00.000
MJD(0) = 1858-11-17 00:00:00.000
MJD(JD) = JD − 2400000.5

1day = 86400 s = 86400000000 /mus = 86400000000000 ns
*/

namespace
{

constexpr grb::type::Float DAY_IN_SEC       = 86400.0;
constexpr grb::type::Float DAY_IN_MICROSEC  = DAY_IN_SEC * 1000000.0;
constexpr grb::type::Float DAY_IN_NANOSEC   = DAY_IN_SEC * 1000000000.0;
constexpr grb::type::Float UNIX_EPOCH_IN_JD = 2440587.5; // days
constexpr grb::type::Float JD_TO_MJD        = 2400000.5; // days
constexpr grb::type::Float EPSILON          = 0.0000000000001; // 10^-13

} // namespace

namespace grb
{

/** ***********************************************************************************************/

type::Float
Coordinates::getT()
{
  switch (_dateType)
  {
    case type::UNIX_DATE:
      return getTimeUnix();
    case type::JULIAN_DATE:
      return getTimeJD();
    case type::MODIFIED_JULIAN_DATE:
      return getTimeMJD();
    default:
      return _u.common.x0;
  };
}

type::Float
Coordinates::getTimeUnix()
{
  return _u.common.x0;
}

type::Float
Coordinates::getTimeJD()
{
  return _u.common.x0;
}

type::Float
Coordinates::getTimeMJD()
{
  return _u.common.x0;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCarX()
{
  return _u.cartesian.x;
}

type::Float
Coordinates::getCarY()
{
  return _u.cartesian.y;
}

type::Float
Coordinates::getCarZ()
{
  return _u.cartesian.z;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCylRho()
{
  return _u.cylindrical.rho;
}

type::Float
Coordinates::getCylPhi()
{
  return _u.cylindrical.phi;
}

type::Float
Coordinates::getCylZ()
{
  return _u.cylindrical.rho;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getSphR()
{
  return _u.spherical.r;
}

type::Float
Coordinates::getSphPhi()
{
  return _u.spherical.phi;
}

type::Float
Coordinates::getSphTheta()
{
  return _u.spherical.theta;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCelRightAscension()
{
  return _u.celestial.longitude;
}

type::Float
Coordinates::getCelDeclination()
{
  return _u.celestial.latitude;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCelLongnitude()
{
  return _u.celestial.longitude;
}

type::Float
Coordinates::getCelLatitude()
{
  return _u.celestial.latitude;
}

/** ***********************************************************************************************/

bool
Coordinates::isValid()
{
  if (std::fabs(_u.common.x0) > EPSILON)
    return true;

  return false;
}

} // namespace grb
