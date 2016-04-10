#include "Common/Global.h"

#pragma once

namespace grb
{


class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType type = type::COORDINATE_SYSTEM_UNDEFINED)
    : _type(type), _coord_flag(0.0), _horizontal(0.0), _vertical(0.0)
  {
  }

  type::CoordinateSystemType getType() const { return _type; }
  void setType(type::CoordinateSystemType type) { _type = type; }

  const type::Float& getCoordFlag() const { return _coord_flag; }
  const type::Float& getH() const { return _horizontal; }
  const type::Float& getV() const { return _vertical; }

  type::Float& getCoordFlag() { return _coord_flag; }
  type::Float& getH() { return _horizontal; }
  type::Float& getV() { return _vertical; }

private:
  type::CoordinateSystemType _type;
  type::Float _coord_flag;
  type::Float _horizontal;
  type::Float _vertical;
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
  const type::Float& getMJD() const { return _mjd; }
private:
  type::Float _mjd;
};

class Duration
{
public:
  Duration()
    : _isPresent(false), _mod(-1), _duration(0.0), _error(0.0), _emin(0), _emax(0)
  { }
  ~Duration()
  { _range.clear(); }

  bool isPresent() const { return _isPresent; }
  void setPresent(bool val = true) { _isPresent = val; }

  const type::Index& getMod() const { return _mod; }
  const type::Float& getDuration() const { return _duration; }
  const type::Float& getError() const { return _error; }
  const type::IntegerRange& getRange() const { return _range; }
  const type::Integer& getEmin() const { return _emin; }
  const type::Integer& getEmax() const { return _emax; }

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

  const type::Float& getDuration() const { return _duration; }
  const type::String& getNotes() const { return _notes; }

  type::Float& getDuration() { return _duration; }
  type::String& getNotes() { return _notes; }

private:
  bool _isPresent;
  type::Float _duration;
  type::String _notes;
};

}
