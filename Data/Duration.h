#include "Common/Global.h"
#include "Data/UnitMapper.h"

#pragma once

namespace grb
{

class DurationBase
{
public:
  DurationBase(type::UnitType durationUnitType = type::UNDEFINED_UNIT)
    : _duration(0.0), _durationUnitType(durationUnitType), _isPresent(false)
  {
  }

  virtual ~DurationBase() = default;

  type::UnitType getDurationUnitType() const
  {
    return _durationUnitType;
  }

  void setDurationUnitType(const type::UnitType durationUnitType)
  {
    _durationUnitType = durationUnitType;
  }

  type::Float& getDuration()
  {
    return _duration;
  }

  bool isPresent() const
  {
    return _isPresent;
  }

  void setPresent(bool val = true)
  {
    _isPresent = val;
  }

  virtual bool isValid() = 0;

protected:

private:
  type::Float _duration;
  type::UnitType _durationUnitType;
  bool _isPresent;
};

class Energy
{
public:
  Energy(type::UnitType energyUnitType = type::UNDEFINED_UNIT)
    : _energyUnitType(energyUnitType), _emin(0), _emax(0)
  {
  }

  virtual ~Energy()
  {
    _range.clear();
  }

  type::UnitType getEnergyUnitType() const
  {
    return _energyUnitType;
  }

  void setEnergyUnitType(const type::UnitType energyUnitType)
  {
    _energyUnitType = energyUnitType;
  }

  type::Integer& getEmin()
  {
    return _emin;
  }

  type::Integer& getEmax()
  {
    return _emax;
  }

  type::IntegerRange& getRange()
  {
    return _range;
  }

private:
  type::UnitType _energyUnitType;
  type::Integer _emin;
  type::Integer _emax;
  type::IntegerRange _range;
};

class Duration : public DurationBase, public Energy
{
public:
  Duration(type::UnitType durationUnitType = type::UNDEFINED_UNIT,
           type::UnitType energyUnitType = type::UNDEFINED_UNIT)
    : DurationBase(durationUnitType), Energy(energyUnitType),
      _mod(-1), _error(0.0)
  {
  }

  type::Index& getMod()
  {
    return _mod;
  }

  type::Float& getError()
  {
    return _error;
  }

  bool isValid();

private:
  type::Index _mod;
  type::Float _error;
};

class DurationOther : public DurationBase
{
public:
  DurationOther(type::UnitType unitType = type::UNDEFINED_UNIT)
    : DurationBase(unitType)
  {
  }

  ~DurationOther() = default;

  type::String& getNotes()
  {
    return _notes;
  }

  bool isValid();

private:
  type::String _notes;
};

}
