#include "TimePoint.h"

#include <cmath>

//typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
/*
JD(0) = -4713-01-01 12:00:00.000
MJD(0) = 1858-11-17 00:00:00.000
MJD(JD) = JD − 2400000.5

1day = 86400 s = 86400000000 /mus = 86400000000000 ns
*/


namespace grb
{

namespace
{
constexpr type::Float DAY_IN_SEC       = 86400.0;
constexpr type::Float DAY_IN_MICROSEC  = DAY_IN_SEC * 1000000.0;
constexpr type::Float DAY_IN_NANOSEC   = DAY_IN_SEC * 1000000000.0;
constexpr type::Float UNIX_EPOCH_IN_JD = 2440587.5; // days
constexpr type::Float JD_TO_MJD        = 2400000.5; // days
constexpr type::Float EPSILON          = 0.0000000000001; // 10^-13
}


TimePoint::TimePoint(type::DateTimeType type)
  : _type(type), _time(0.0), _timeUnitType(type::UNIT_TYPE_UNDEFINED)
{ }

type::DateTimeType
TimePoint::getType() const
{
  return _type;
}

const type::Float&
TimePoint::getTime() const
{
  switch (_type)
  {
    case type::UNIX:
      return getTimeUnix();
    case type::JULIAN_DATE:
      return getTimeJD();
    case type::MODIFIED_JULIAN_DATE:
      return getTimeMJD();
    default:
      return _time;
  };
}

const type::Float&
TimePoint::getTimeUnix() const
{
  return _time;
}

const type::Float&
TimePoint::getTimeJD() const
{
  return _time;
}

const type::Float&
TimePoint::getTimeMJD() const
{
  return _time;
}

type::Float&
TimePoint::getTime()
{
  return _time;
}

void
TimePoint::setTimeUnitType(type::UnitType unitType)
{
  _timeUnitType = unitType;
}


bool
TimePoint::isValid()
{
  if (std::fabs(_time) > EPSILON)
    return true;

  return false;
}

type::Float
TimePoint::convertJDtoMJD()
{
  return _time;
}

type::Float
TimePoint::convertJDtoUNIX()
{
  return _time;
}

type::Float
TimePoint::convertMJDtoJD()
{
  return _time;
}

type::Float
TimePoint::convertMJDtoUNIX()
{
  return _time;
}

type::Float
TimePoint::convertUNIXtoJD()
{
  return _time;
}

type::Float
TimePoint::convertUNIXtoMJD()
{
  return _time;
}

}
