#include "TimePoint.h"

//typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
/*
JD(0) = -4713-01-01 12:00:00.000
MJD(0) = 1858-11-17 00:00:00.000
MJD(JD) = JD − 2400000.5

1day = 86400 s = 86400000000 /mus = 86400000000000 ns
*/


namespace grb
{

TimePoint::TimePoint(type::DateTimeType type)
  : _type(type), _time(0.0)
{ }

type::DateTimeType
TimePoint::getType() const
{
  return _type;
}

const type::Float&
TimePoint::getTime() const
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

}
