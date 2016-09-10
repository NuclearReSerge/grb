#include "Common/Global.h"
#include "Data/UnitMapper.h"

#pragma once

namespace grb
{

class Duration
{
public:
  Duration()
    : _isPresent(false), _mod(-1), _duration(0.0), _error(0.0), _emin(0), _emax(0),
      _durationUnitType(type::UNDEFINED_UNIT), _energyUnitType(type::UNDEFINED_UNIT)
  {
  }

  ~Duration()
  {
    _range.clear();
  }

  bool isPresent() const
  {
    return _isPresent;
  }

  void setPresent(bool val = true)
  {
    _isPresent = val;
  }

  type::Index& getMod()
  {
    return _mod;
  }

  type::Float& getDuration()
  {
    return _duration;
  }

  type::Float& getError()
  {
    return _error;
  }

  type::IntegerRange& getRange()
  {
    return _range;
  }

  type::Integer& getEmin()
  {
    return _emin;
  }

  type::Integer& getEmax()
  {
    return _emax;
  }

protected:
  friend class CatalogEntryGrbcat;

  void setDurationUnitType(type::UnitType unitType)
  {
    _durationUnitType = unitType;
  }

  void setEnergyUnitType(type::UnitType unitType)
  {
    _energyUnitType = unitType;
  }

  bool isValid();

private:
  bool _isPresent;
  type::Index _mod;
  type::Float _duration;
  type::Float _error;
  type::IntegerRange _range;
  type::Integer _emin;
  type::Integer _emax;
  type::UnitType _durationUnitType;
  type::UnitType _energyUnitType;

};

class DurationOther
{
public:
  DurationOther()
    : _isPresent(false), _duration(0.0), _durationUnitType(type::UNDEFINED_UNIT)
  {
  }

  ~DurationOther() = default;

  bool isPresent() const
  {
    return _isPresent;
  }

  void setPresent(bool val = true)
  {
    _isPresent = val;
  }

  type::Float& getDuration()
  {
    return _duration;
  }

  type::String& getNotes()
  {
    return _notes;
  }

protected:
  friend class CatalogEntryGrbcat;
  void setDurationUnitType(type::UnitType unitType)
  {
    _durationUnitType = unitType;
  }

  bool isValid();

private:
  bool _isPresent;
  type::Float _duration;
  type::UnitType _durationUnitType;
  type::String _notes;
};

}
