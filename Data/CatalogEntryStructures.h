#include "Common/Global.h"

#pragma once

namespace grb
{

struct CoordinateSystemUndefined
{
  type::Float horizontal;
  type::Float vertical;
};

struct CoordinateSystemEquinox
{
  type::Float rightAscension;
  type::Float declination;
};

struct CoordinateSystemGalactic
{
  type::Float latitude;
  type::Float longitude;
};

class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType type = type::COORDINATE_SYSTEM_UNDEFINED)
    : _type(type), _coord_flag(0.0)
  {
    _u.undefined.horizontal = 0.0;
    _u.undefined.vertical = 0.0;
  }

  type::CoordinateSystemType getType() const { return _type; }
  void setType(type::CoordinateSystemType type) { _type = type; }
  type::Float& getCoordFlag() { return _coord_flag; }
  type::Float& getH()
  {
    switch (_type)
    {
      case type::J2000:
        return _u.j2000.rightAscension;
      case type::B1950:
        return _u.b1950.rightAscension;
      case type::GALACTIC:
        return _u.galactic.longitude;
      default:
        return _u.undefined.horizontal;
    }
  }
  type::Float& getV()
  {
    switch (_type)
    {
      case type::J2000:
        return _u.j2000.declination;
      case type::B1950:
        return _u.b1950.declination;
      case type::GALACTIC:
        return _u.galactic.latitude;
      default:
        return _u.undefined.vertical;
    }
  }

private:
  type::CoordinateSystemType _type;
  type::Float _coord_flag;
  union
  {
    CoordinateSystemUndefined undefined;
    CoordinateSystemEquinox b1950;
    CoordinateSystemEquinox j2000;
    CoordinateSystemGalactic galactic;
  } _u;
};

//typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
/*
JD(0) = -4713-01-01 12:00:00.000
MJD(0) = 1858-11-17 00:00:00.000
MJD(JD) = JD − 2400000.5

1day = 86400 s = 86400000000 /mus = 86400000000000 ns
*/


class TimePoint
{
public:
  TimePoint()
    : _mjd(0.0)
  { }

  type::Float& getMJD() { return _mjd; }
private:
  type::Float _mjd;
};

class Duration
{
public:
  Duration()
    : _isPresent(false), _mod(), _duration(0.0), _error(0.0), _emin(0), _emax(0)
  { }
  ~Duration()
  { _range.clear(); }

  bool isPresent() const { return _isPresent; }
  void setPresent(bool val = true) { _isPresent = val; }
  type::Index& getMod() { return _mod; }
  type::Float& getDuration() { return _duration; }
  type::Float& getError() { return _error; }
  type::IntegerRange& getRange() { return _range; }
  type::Integer& getEmin() { return _emin; }
  type::Integer& getEmax() { return _emax; }

private:
  bool _isPresent;
  type::Index _mod;
  type::Float _duration;
  type::Float _error;
  type::IntegerRange _range;
  type::Integer _emin;
  type::Integer _emax;
};

class DurationOther
{
public:
  DurationOther()
    : _isPresent(false), _duration(0.0)
  { }
  ~DurationOther()
  { }

  bool isPresent() const { return _isPresent; }
  void setPresent(bool val = true) { _isPresent = val; }
  type::Float& getDuration() { return _duration; }
  type::String& getNotes() { return _notes; }

private:
  bool _isPresent;
  type::Float _duration;
  type::String _notes;
};

}
